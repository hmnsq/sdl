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
#ضمن "../../SDL_internal.h"

#ضمن "../../events/SDL_pen_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_x11pen.h"
#ضمن "SDL_x11video.h"
#ضمن "SDL_x11xinput2.h"

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
ساكن bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, ثابت XIDeviceInfo *dev)
{
    ثابت SDL_VideoData *data = _this->internal;
    لكل (صحيح i = 0; i < dev->عدد_classes; i++) {
        ثابت XIAnyClassInfo *classinfo = dev->classes[i];
        إذا (classinfo->type == XIValuatorClass) {
            ثابت XIValuatorClassInfo *val_classinfo = (ثابت XIValuatorClassInfo *)classinfo;
            إذا (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                أرجع true;
            }
        }
    }

    أرجع false;
}

// Heuristically determines if device is an eraser
ساكن bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, صحيح deviceid, حرف *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    إذا (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        صحيح format_return;
        unsigned long عدد_اشیاء_return;
        unsigned long bytes_after_return;
        unsigned حرف *tooltype_name_info = عدم;

        // Try Wacom-specific method
        إذا (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &عدد_اشیاء_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != عدم && عدد_اشیاء_return > 0) {

            bool result = false;
            حرف *tooltype_name = عدم;

            إذا (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                إذا (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } وإلا إذا (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (حرف *)tooltype_name_info;
            }

            إذا (tooltype_name) {
                إذا (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                إذا (tooltype_name != (حرف *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                أرجع result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    أرجع (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
ساكن size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, صحيح deviceid, Atom property, Sint32 *dest, size_t max_الفاظ)
{
    ثابت SDL_VideoData *data = _this->internal;
    Atom type_return;
    صحيح format_return;
    unsigned long عدد_اشیاء_return;
    unsigned long bytes_after_return;
    unsigned حرف *output;

    إذا (property == None) {
        أرجع 0;
    }

    إذا (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_الفاظ, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &عدد_اشیاء_return, &bytes_after_return,
                                     &output) ||
        عدد_اشیاء_return == 0 || output == عدم) {
        أرجع 0;
    }

    إذا (type_return == XA_INTEGER) {
        صحيح k;
        ثابت صحيح to_copy = SDL_min(max_الفاظ, عدد_اشیاء_return);

        إذا (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            لكل (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } وإلا إذا (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            لكل (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } وإلا {
            SDL_memcpy(dest, output, حجم(Sint32) * to_copy);
        }
        X11_XFree(output);
        أرجع to_copy;
    }

    أرجع 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
ساكن bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, صحيح deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    صحيح result;

    إذا ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        أرجع true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    أرجع false;
}

// Check if a Wacom device is in proximity of the tablet
ساكن bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, صحيح deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    إذا (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        أرجع true;
    }
    أرجع false;
}


تعريفنوع بنية FindPenByDeviceIDData
{
    صحيح x11_deviceid;
    فراغ *handle;
} FindPenByDeviceIDData;

ساكن bool FindPenByDeviceID(فراغ *handle, فراغ *userdata)
{
    ثابت X11_PenHandle *x11_handle = (ثابت X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    إذا (x11_handle->x11_deviceid != data->x11_deviceid) {
        أرجع false;
    }
    data->handle = handle;
    أرجع true;
}

X11_PenHandle *X11_FindPenByDeviceID(صحيح deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = عدم;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    أرجع (X11_PenHandle *) data.handle;
}

ساكن X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, ثابت XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = عدم;

    إذا ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        أرجع عدم;  // Only track physical devices that are enabled and look like pens
    } وإلا إذا ((handle = X11_FindPenByDeviceID(dev->deviceid)) != عدم) {
        أرجع handle;  // already have this pen, skip it.
    } وإلا إذا ((handle = SDL_calloc(1, حجم(*handle))) == عدم) {
        أرجع عدم;  // oh well.
    }

    لكل (صحيح i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    صحيح total_buttons = 0;
    لكل (صحيح i = 0; i < dev->عدد_classes; i++) {
        ثابت XIAnyClassInfo *classinfo = dev->classes[i];
        إذا (classinfo->type == XIButtonClass) {
            ثابت XIButtonClassInfo *button_classinfo = (ثابت XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->عدد_buttons;
        } وإلا إذا (classinfo->type == XIValuatorClass) {
            ثابت XIValuatorClassInfo *val_classinfo = (ثابت XIValuatorClassInfo *)classinfo;
            ثابت Sint8 valuator_nr = val_classinfo->نمبر_2;
            ثابت Atom vname = val_classinfo->label;
            ثابت عائم min = (عائم)val_classinfo->min;
            ثابت عائم max = (عائم)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_گنتی;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            إذا (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } وإلا إذا (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } وإلا إذا (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } وإلا {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            إذا (use_this_axis) {
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

    ثابت bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.عدد_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    إذا (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    إذا (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, عدم, &peninfo, handle, in_proximity);
    إذا (!handle->pen) {
        SDL_free(handle);
        أرجع عدم;
    }

    أرجع handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, صحيح deviceid)
{
    إذا (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        صحيح عدد_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &عدد_device_info);
        إذا (device_info) {
            SDL_assert(عدد_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            أرجع handle;
        }
    }
    أرجع عدم;
}

فراغ X11_RemovePenByDeviceID(صحيح deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    إذا (handle) {
        SDL_RemovePenDevice(0, عدم, handle->pen);
        SDL_free(handle);
    }
}

فراغ X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, صحيح deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    إذا (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

فراغ X11_InitPen(SDL_VideoDevice *_this)
{
    إذا (!X11_Xinput2IsInitialized()) {
        أرجع;  // we need XIQueryDevice() for this.
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
    صحيح عدد_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &عدد_device_info);
    إذا (device_info) {
        لكل (صحيح i = 0; i < عدد_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

ساكن فراغ X11_FreePenHandle(SDL_PenID instance_id, فراغ *handle, فراغ *userdata)
{
    SDL_free(handle);
}

فراغ X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, عدم);
}

ساكن فراغ X11_XInput2NormalizePenAxes(ثابت X11_PenHandle *pen, عائم *coords)
{
    // Normalise axes
    لكل (صحيح axis = 0; axis < SDL_PEN_AXIS_گنتی; ++axis) {
        ثابت صحيح valuator = pen->valuator_for_axis[axis];
        إذا (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            استمر;
        }

        عائم قدر = coords[axis];
        ثابت عائم min = pen->axis_min[axis];
        ثابت عائم max = pen->axis_max[axis];

        إذا (axis == SDL_PEN_AXIS_SLIDER) {
            قدر += pen->slider_bias;
        }

        // min ... 0 ... max
        إذا (min < 0.0) {
            // Normalise so that 0 remains 0.0
            إذا (قدر < 0) {
                قدر = قدر / (-min);
            } وإلا {
                إذا (max == 0.0f) {
                    قدر = 0.0f;
                } وإلا {
                    قدر = قدر / max;
                }
            }
        } وإلا {
            // 0 ... min ... max
            // including 0.0 = min
            إذا (max == 0.0f) {
                قدر = 0.0f;
            } وإلا {
                قدر = (قدر - min) / max;
            }
        }

        بدل (axis) {
            حالة SDL_PEN_AXIS_XTILT:
            حالة SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                اكسر;

            حالة SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                قدر *= 180.0f;
                قدر += pen->rotation_bias;

                // handle simple over/underflow
                إذا (قدر >= 180.0f) {
                    قدر -= 360.0f;
                } وإلا إذا (قدر < -180.0f) {
                    قدر += 360.0f;
                }
                اكسر;

            افتراضي:
                اكسر;
        }

        coords[axis] = قدر;
    }
}

فراغ X11_PenAxesFromValuators(ثابت X11_PenHandle *pen,
                              ثابت مزدوج *داخلہ_اقدار, ثابت unsigned حرف *mask, صحيح mask_len,
                              عائم axis_اقدار[SDL_PEN_AXIS_گنتی])
{
    لكل (صحيح i = 0; i < SDL_PEN_AXIS_گنتی; i++) {
        ثابت صحيح valuator = pen->valuator_for_axis[i];
        إذا ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_اقدار[i] = 0.0f;
        } وإلا {
            axis_اقدار[i] = (عائم)داخلہ_اقدار[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_اقدار);
}

#وإلا

فراغ X11_InitPen(SDL_VideoDevice *_this)
{
    (فراغ) _this;
}

فراغ X11_QuitPen(SDL_VideoDevice *_this)
{
    (فراغ) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

