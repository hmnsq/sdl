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
    for (int i = 0; i < dev->नुमेरो_classes; i++) {
        const XIAnyClassInfo *classinfo = dev->classes[i];
        if (classinfo->type == XIValuatorClass) {
            const XIValuatorClassInfo *val_classinfo = (const XIValuatorClassInfo *)classinfo;
            if (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                return true;
            }
        }
    }

    return false;
}

// Heuristically determines if device is an eraser
static bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, int deviceid, char *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    if (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        int format_return;
        unsigned long नुमेरो_मगा_बागाय_return;
        unsigned long bytes_after_return;
        unsigned char *tooltype_name_info = NULL;

        // Try Wacom-specific method
        if (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &नुमेरो_मगा_बागाय_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != NULL && नुमेरो_मगा_बागाय_return > 0) {

            bool result = false;
            char *tooltype_name = NULL;

            if (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                if (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } else if (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (char *)tooltype_name_info;
            }

            if (tooltype_name) {
                if (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                if (tooltype_name != (char *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                return result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    return (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
static size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, int deviceid, Atom property, Sint32 *dest, size_t max_मगा_सालिता)
{
    const SDL_VideoData *data = _this->internal;
    Atom type_return;
    int format_return;
    unsigned long नुमेरो_मगा_बागाय_return;
    unsigned long bytes_after_return;
    unsigned char *output;

    if (property == None) {
        return 0;
    }

    if (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_मगा_सालिता, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &नुमेरो_मगा_बागाय_return, &bytes_after_return,
                                     &output) ||
        नुमेरो_मगा_बागाय_return == 0 || output == NULL) {
        return 0;
    }

    if (type_return == XA_INTEGER) {
        int k;
        const int to_copy = SDL_min(max_मगा_सालिता, नुमेरो_मगा_बागाय_return);

        if (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            for (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } else if (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            for (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } else {
            SDL_memcpy(dest, output, sizeof(Sint32) * to_copy);
        }
        X11_XFree(output);
        return to_copy;
    }

    return 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
static bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, int deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    int result;

    if ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        return true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    return false;
}

// Check if a Wacom device is in proximity of the tablet
static bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, int deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    if (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        return true;
    }
    return false;
}


typedef struct FindPenByDeviceIDData
{
    int x11_deviceid;
    void *handle;
} FindPenByDeviceIDData;

static bool FindPenByDeviceID(void *handle, void *userdata)
{
    const X11_PenHandle *x11_handle = (const X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    if (x11_handle->x11_deviceid != data->x11_deviceid) {
        return false;
    }
    data->handle = handle;
    return true;
}

X11_PenHandle *X11_FindPenByDeviceID(int deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = NULL;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    return (X11_PenHandle *) data.handle;
}

static X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, const XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = NULL;

    if ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        return NULL;  // Only track physical devices that are enabled and look like pens
    } else if ((handle = X11_FindPenByDeviceID(dev->deviceid)) != NULL) {
        return handle;  // already have this pen, skip it.
    } else if ((handle = SDL_calloc(1, sizeof(*handle))) == NULL) {
        return NULL;  // oh well.
    }

    for (int i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    int total_buttons = 0;
    for (int i = 0; i < dev->नुमेरो_classes; i++) {
        const XIAnyClassInfo *classinfo = dev->classes[i];
        if (classinfo->type == XIButtonClass) {
            const XIButtonClassInfo *button_classinfo = (const XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->नुमेरो_buttons;
        } else if (classinfo->type == XIValuatorClass) {
            const XIValuatorClassInfo *val_classinfo = (const XIValuatorClassInfo *)classinfo;
            const Sint8 valuator_nr = val_classinfo->नुमेरो_3;
            const Atom vname = val_classinfo->label;
            const float min = (float)val_classinfo->min;
            const float max = (float)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_बिलांग;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            if (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } else if (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } else if (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } else {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            if (use_this_axis) {
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
    peninfo.नुमेरो_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    if (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    if (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, NULL, &peninfo, handle, in_proximity);
    if (!handle->pen) {
        SDL_free(handle);
        return NULL;
    }

    return handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, int deviceid)
{
    if (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        int नुमेरो_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &नुमेरो_device_info);
        if (device_info) {
            SDL_assert(नुमेरो_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            return handle;
        }
    }
    return NULL;
}

void X11_RemovePenByDeviceID(int deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    if (handle) {
        SDL_RemovePenDevice(0, NULL, handle->pen);
        SDL_free(handle);
    }
}

void X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, int deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    if (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

void X11_InitPen(SDL_VideoDevice *_this)
{
    if (!X11_Xinput2IsInitialized()) {
        return;  // we need XIQueryDevice() for this.
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
    int नुमेरो_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &नुमेरो_device_info);
    if (device_info) {
        for (int i = 0; i < नुमेरो_device_info; i++) {
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
    for (int axis = 0; axis < SDL_PEN_AXIS_बिलांग; ++axis) {
        const int valuator = pen->valuator_for_axis[axis];
        if (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            continue;
        }

        float हालागा = coords[axis];
        const float min = pen->axis_min[axis];
        const float max = pen->axis_max[axis];

        if (axis == SDL_PEN_AXIS_SLIDER) {
            हालागा += pen->slider_bias;
        }

        // min ... 0 ... max
        if (min < 0.0) {
            // Normalise so that 0 remains 0.0
            if (हालागा < 0) {
                हालागा = हालागा / (-min);
            } else {
                if (max == 0.0f) {
                    हालागा = 0.0f;
                } else {
                    हालागा = हालागा / max;
                }
            }
        } else {
            // 0 ... min ... max
            // including 0.0 = min
            if (max == 0.0f) {
                हालागा = 0.0f;
            } else {
                हालागा = (हालागा - min) / max;
            }
        }

        switch (axis) {
            case SDL_PEN_AXIS_XTILT:
            case SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                break;

            case SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                हालागा *= 180.0f;
                हालागा += pen->rotation_bias;

                // handle simple over/underflow
                if (हालागा >= 180.0f) {
                    हालागा -= 360.0f;
                } else if (हालागा < -180.0f) {
                    हालागा += 360.0f;
                }
                break;

            default:
                break;
        }

        coords[axis] = हालागा;
    }
}

void X11_PenAxesFromValuators(const X11_PenHandle *pen,
                              const double *पासोक_मगा_हालागा, const unsigned char *mask, int mask_len,
                              float axis_मगा_हालागा[SDL_PEN_AXIS_बिलांग])
{
    for (int i = 0; i < SDL_PEN_AXIS_बिलांग; i++) {
        const int valuator = pen->valuator_for_axis[i];
        if ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_मगा_हालागा[i] = 0.0f;
        } else {
            axis_मगा_हालागा[i] = (float)पासोक_मगा_हालागा[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_मगा_हालागा);
}

#else

void X11_InitPen(SDL_VideoDevice *_this)
{
    (void) _this;
}

void X11_QuitPen(SDL_VideoDevice *_this)
{
    (void) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

