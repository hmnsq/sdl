/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#include "../../events/SDL_pen_c.h"
#include "../SDL_sysvideo.h"
#include "SDL_x11pen.h"
#include "SDL_x11video.h"
#include "SDL_x11xinput2.h"

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
static bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, const XIDeviceInfo *dev)
{
    const SDL_VideoData *data = _this->internal;
    အတွက် (ကိန်းပြည့် i = 0; i < dev->num_classes; i++) {
        const XIAnyClassInfo *classinfo = dev->classes[i];
        အကယ်၍ (classinfo->type == XIValuatorClass) {
            const XIValuatorClassInfo *val_classinfo = (const XIValuatorClassInfo *)classinfo;
            အကယ်၍ (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                ပြန်ပေး true;
            }
        }
    }

    ပြန်ပေး false;
}

// Heuristically determines if device is an eraser
static bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, ကိန်းပြည့် deviceid, var_na *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    အကယ်၍ (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        ကိန်းပြည့် format_return;
        unsigned long num_items_return;
        unsigned long bytes_after_return;
        unsigned var_na *tooltype_name_info = NULL;

        // Try Wacom-specific method
        အကယ်၍ (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &num_items_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != NULL && num_items_return > 0) {

            bool result = false;
            var_na *tooltype_name = NULL;

            အကယ်၍ (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                အကယ်၍ (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } မဟုတ်ပါက အကယ်၍ (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (var_na *)tooltype_name_info;
            }

            အကယ်၍ (tooltype_name) {
                အကယ်၍ (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                အကယ်၍ (tooltype_name != (var_na *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                ပြန်ပေး result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    ပြန်ပေး (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
static size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, ကိန်းပြည့် deviceid, Atom property, Sint32 *dest, size_t max_words)
{
    const SDL_VideoData *data = _this->internal;
    Atom type_return;
    ကိန်းပြည့် format_return;
    unsigned long num_items_return;
    unsigned long bytes_after_return;
    unsigned var_na *output;

    အကယ်၍ (property == None) {
        ပြန်ပေး 0;
    }

    အကယ်၍ (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_words, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &num_items_return, &bytes_after_return,
                                     &output) ||
        num_items_return == 0 || output == NULL) {
        ပြန်ပေး 0;
    }

    အကယ်၍ (type_return == XA_INTEGER) {
        ကိန်းပြည့် k;
        const ကိန်းပြည့် to_copy = SDL_min(max_words, num_items_return);

        အကယ်၍ (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            အတွက် (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } မဟုတ်ပါက အကယ်၍ (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            အတွက် (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } မဟုတ်ပါက {
            SDL_memcpy(dest, output, parimaa_na(Sint32) * to_copy);
        }
        X11_XFree(output);
        ပြန်ပေး to_copy;
    }

    ပြန်ပေး 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
static bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, ကိန်းပြည့် deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    ကိန်းပြည့် result;

    အကယ်၍ ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        ပြန်ပေး true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    ပြန်ပေး false;
}

// Check if a Wacom device is in proximity of the tablet
static bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, ကိန်းပြည့် deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    အကယ်၍ (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        ပြန်ပေး true;
    }
    ပြန်ပေး false;
}


typedef sa_nracanaa FindPenByDeviceIDData
{
    ကိန်းပြည့် x11_deviceid;
    void *handle;
} FindPenByDeviceIDData;

static bool FindPenByDeviceID(void *handle, void *userdata)
{
    const X11_PenHandle *x11_handle = (const X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    အကယ်၍ (x11_handle->x11_deviceid != data->x11_deviceid) {
        ပြန်ပေး false;
    }
    data->handle = handle;
    ပြန်ပေး true;
}

X11_PenHandle *X11_FindPenByDeviceID(ကိန်းပြည့် deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = NULL;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    ပြန်ပေး (X11_PenHandle *) data.handle;
}

static X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, const XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = NULL;

    အကယ်၍ ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        ပြန်ပေး NULL;  // Only track physical devices that are enabled and look like pens
    } မဟုတ်ပါက အကယ်၍ ((handle = X11_FindPenByDeviceID(dev->deviceid)) != NULL) {
        ပြန်ပေး handle;  // already have this pen, skip it.
    } မဟုတ်ပါက အကယ်၍ ((handle = SDL_calloc(1, parimaa_na(*handle))) == NULL) {
        ပြန်ပေး NULL;  // oh well.
    }

    အတွက် (ကိန်းပြည့် i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    ကိန်းပြည့် total_buttons = 0;
    အတွက် (ကိန်းပြည့် i = 0; i < dev->num_classes; i++) {
        const XIAnyClassInfo *classinfo = dev->classes[i];
        အကယ်၍ (classinfo->type == XIButtonClass) {
            const XIButtonClassInfo *button_classinfo = (const XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->num_buttons;
        } မဟုတ်ပါက အကယ်၍ (classinfo->type == XIValuatorClass) {
            const XIValuatorClassInfo *val_classinfo = (const XIValuatorClassInfo *)classinfo;
            const Sint8 valuator_nr = val_classinfo->number;
            const Atom vname = val_classinfo->label;
            const float min = (float)val_classinfo->min;
            const float max = (float)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_COUNT;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            အကယ်၍ (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } မဟုတ်ပါက အကယ်၍ (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } မဟုတ်ပါက အကယ်၍ (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } မဟုတ်ပါက {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            အကယ်၍ (use_this_axis) {
                capabilities |= SDL_GetPenCapabilityFromAxis(axis);
                handle->valuator_for_axis[axis] = valuator_nr;
                handle->axis_min[axis] = min;
                handle->axis_max[axis] = max;
            }
        }
    }

    // We have a pen if and only if the device measures pressure.
    // We checked this in X11_XInput2DeviceIsPen, so just assert it here.
    SDL_assert(capabilities & SDL_PEN_CAPABILITY_PRESSURE);

    const bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.num_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    အကယ်၍ (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    အကယ်၍ (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, NULL, &peninfo, handle, in_proximity);
    အကယ်၍ (!handle->pen) {
        SDL_free(handle);
        ပြန်ပေး NULL;
    }

    ပြန်ပေး handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, ကိန်းပြည့် deviceid)
{
    အကယ်၍ (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        ကိန်းပြည့် num_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &num_device_info);
        အကယ်၍ (device_info) {
            SDL_assert(num_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            ပြန်ပေး handle;
        }
    }
    ပြန်ပေး NULL;
}

void X11_RemovePenByDeviceID(ကိန်းပြည့် deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    အကယ်၍ (handle) {
        SDL_RemovePenDevice(0, NULL, handle->pen);
        SDL_free(handle);
    }
}

void X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, ကိန်းပြည့် deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    အကယ်၍ (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

void X11_InitPen(SDL_VideoDevice *_this)
{
    အကယ်၍ (!X11_Xinput2IsInitialized()) {
        ပြန်ပေး;  // we need XIQueryDevice() for this.
    }

    SDL_VideoData *data = _this->internal;

    #define LOOKUP_PEN_ATOM(X) X11_XInternAtom(data->display, X, False)
    data->atoms.pen_atom_device_product_id = LOOKUP_PEN_ATOM("Device Product ID");
    data->atoms.pen_atom_wacom_serial_ids = LOOKUP_PEN_ATOM("Wacom Serial IDs");
    data->atoms.pen_atom_wacom_tool_type = LOOKUP_PEN_ATOM("Wacom Tool Type");
    data->atoms.pen_atom_abs_pressure = LOOKUP_PEN_ATOM("Abs Pressure");
    data->atoms.pen_atom_abs_tilt_x = LOOKUP_PEN_ATOM("Abs Tilt X");
    data->atoms.pen_atom_abs_tilt_y = LOOKUP_PEN_ATOM("Abs Tilt Y");
    #undef LOOKUP_PEN_ATOM

    // Do an initial check on devices. After this, we'll add/remove individual pens when XI_HierarchyChanged events alert us.
    ကိန်းပြည့် num_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &num_device_info);
    အကယ်၍ (device_info) {
        အတွက် (ကိန်းပြည့် i = 0; i < num_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

static void X11_FreePenHandle(SDL_PenID instance_id, void *handle, void *userdata)
{
    SDL_free(handle);
}

void X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, NULL);
}

static void X11_XInput2NormalizePenAxes(const X11_PenHandle *pen, float *coords)
{
    // Normalise axes
    အတွက် (ကိန်းပြည့် axis = 0; axis < SDL_PEN_AXIS_COUNT; ++axis) {
        const ကိန်းပြည့် valuator = pen->valuator_for_axis[axis];
        အကယ်၍ (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            continue;
        }

        float value = coords[axis];
        const float min = pen->axis_min[axis];
        const float max = pen->axis_max[axis];

        အကယ်၍ (axis == SDL_PEN_AXIS_SLIDER) {
            value += pen->slider_bias;
        }

        // min ... 0 ... max
        အကယ်၍ (min < 0.0) {
            // Normalise so that 0 remains 0.0
            အကယ်၍ (value < 0) {
                value = value / (-min);
            } မဟုတ်ပါက {
                အကယ်၍ (max == 0.0f) {
                    value = 0.0f;
                } မဟုတ်ပါက {
                    value = value / max;
                }
            }
        } မဟုတ်ပါက {
            // 0 ... min ... max
            // including 0.0 = min
            အကယ်၍ (max == 0.0f) {
                value = 0.0f;
            } မဟုတ်ပါက {
                value = (value - min) / max;
            }
        }

        switch (axis) {
            pak_sa SDL_PEN_AXIS_XTILT:
            pak_sa SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                bha_nga;

            pak_sa SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                value *= 180.0f;
                value += pen->rotation_bias;

                // handle simple over/underflow
                အကယ်၍ (value >= 180.0f) {
                    value -= 360.0f;
                } မဟုတ်ပါက အကယ်၍ (value < -180.0f) {
                    value += 360.0f;
                }
                bha_nga;

            default:
                bha_nga;
        }

        coords[axis] = value;
    }
}

void X11_PenAxesFromValuators(const X11_PenHandle *pen,
                              const dviguu_na *input_values, const unsigned var_na *mask, ကိန်းပြည့် mask_len,
                              float axis_values[SDL_PEN_AXIS_COUNT])
{
    အတွက် (ကိန်းပြည့် i = 0; i < SDL_PEN_AXIS_COUNT; i++) {
        const ကိန်းပြည့် valuator = pen->valuator_for_axis[i];
        အကယ်၍ ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_values[i] = 0.0f;
        } မဟုတ်ပါက {
            axis_values[i] = (float)input_values[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_values);
}

#မဟုတ်ပါက

void X11_InitPen(SDL_VideoDevice *_this)
{
    (void) _this;
}

void X11_QuitPen(SDL_VideoDevice *_this)
{
    (void) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

