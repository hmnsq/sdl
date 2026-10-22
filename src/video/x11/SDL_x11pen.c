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
#ಅನ್ತರ್ಭಾವ "../../SDL_internal.h"

#ಅನ್ತರ್ಭಾವ "../../events/SDL_pen_c.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11pen.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11video.h"
#ಅನ್ತರ್ಭಾವ "SDL_x11xinput2.h"

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
ಸ್ಥಿರ bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, ಧ್ರುವ XIDeviceInfo *dev)
{
    ಧ್ರುವ SDL_VideoData *data = _this->internal;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < dev->ಅಂಕೆ_classes; i++) {
        ಧ್ರುವ XIAnyClassInfo *classinfo = dev->classes[i];
        ಯದಿ (classinfo->type == XIValuatorClass) {
            ಧ್ರುವ XIValuatorClassInfo *val_classinfo = (ಧ್ರುವ XIValuatorClassInfo *)classinfo;
            ಯದಿ (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                ಪ್ರತ್ಯಾಗಮ true;
            }
        }
    }

    ಪ್ರತ್ಯಾಗಮ false;
}

// Heuristically determines if device is an eraser
ಸ್ಥಿರ bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ deviceid, ವರ್ಣ *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    ಯದಿ (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        ಪೂರ್ಣಾಙ್ಕ format_return;
        unsigned long ಅಂಕೆ_ವಸ್ತುಗಳು_return;
        unsigned long bytes_after_return;
        unsigned ವರ್ಣ *tooltype_name_info = ರಿಕ್ತ;

        // Try Wacom-specific method
        ಯದಿ (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &ಅಂಕೆ_ವಸ್ತುಗಳು_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != ರಿಕ್ತ && ಅಂಕೆ_ವಸ್ತುಗಳು_return > 0) {

            bool result = false;
            ವರ್ಣ *tooltype_name = ರಿಕ್ತ;

            ಯದಿ (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                ಯದಿ (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } ಅನ್ಯಥಾ ಯದಿ (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (ವರ್ಣ *)tooltype_name_info;
            }

            ಯದಿ (tooltype_name) {
                ಯದಿ (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                ಯದಿ (tooltype_name != (ವರ್ಣ *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                ಪ್ರತ್ಯಾಗಮ result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    ಪ್ರತ್ಯಾಗಮ (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
ಸ್ಥಿರ size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ deviceid, Atom property, Sint32 *dest, size_t max_ಪದಗಳು)
{
    ಧ್ರುವ SDL_VideoData *data = _this->internal;
    Atom type_return;
    ಪೂರ್ಣಾಙ್ಕ format_return;
    unsigned long ಅಂಕೆ_ವಸ್ತುಗಳು_return;
    unsigned long bytes_after_return;
    unsigned ವರ್ಣ *output;

    ಯದಿ (property == None) {
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯದಿ (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_ಪದಗಳು, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &ಅಂಕೆ_ವಸ್ತುಗಳು_return, &bytes_after_return,
                                     &output) ||
        ಅಂಕೆ_ವಸ್ತುಗಳು_return == 0 || output == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯದಿ (type_return == XA_INTEGER) {
        ಪೂರ್ಣಾಙ್ಕ k;
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ to_copy = SDL_min(max_ಪದಗಳು, ಅಂಕೆ_ವಸ್ತುಗಳು_return);

        ಯದಿ (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            ಪ್ರತಿ (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ಅನ್ಯಥಾ ಯದಿ (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            ಪ್ರತಿ (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ಅನ್ಯಥಾ {
            SDL_memcpy(dest, output, ಪರಿಮಾಣ(Sint32) * to_copy);
        }
        X11_XFree(output);
        ಪ್ರತ್ಯಾಗಮ to_copy;
    }

    ಪ್ರತ್ಯಾಗಮ 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
ಸ್ಥಿರ bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    ಪೂರ್ಣಾಙ್ಕ result;

    ಯದಿ ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        ಪ್ರತ್ಯಾಗಮ true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    ಪ್ರತ್ಯಾಗಮ false;
}

// Check if a Wacom device is in proximity of the tablet
ಸ್ಥಿರ bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    ಯದಿ (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}


ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FindPenByDeviceIDData
{
    ಪೂರ್ಣಾಙ್ಕ x11_deviceid;
    ಶೂನ್ಯ *handle;
} FindPenByDeviceIDData;

ಸ್ಥಿರ bool FindPenByDeviceID(ಶೂನ್ಯ *handle, ಶೂನ್ಯ *userdata)
{
    ಧ್ರುವ X11_PenHandle *x11_handle = (ಧ್ರುವ X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    ಯದಿ (x11_handle->x11_deviceid != data->x11_deviceid) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    data->handle = handle;
    ಪ್ರತ್ಯಾಗಮ true;
}

X11_PenHandle *X11_FindPenByDeviceID(ಪೂರ್ಣಾಙ್ಕ deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = ರಿಕ್ತ;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    ಪ್ರತ್ಯಾಗಮ (X11_PenHandle *) data.handle;
}

ಸ್ಥಿರ X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, ಧ್ರುವ XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = ರಿಕ್ತ;

    ಯದಿ ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;  // Only track physical devices that are enabled and look like pens
    } ಅನ್ಯಥಾ ಯದಿ ((handle = X11_FindPenByDeviceID(dev->deviceid)) != ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ handle;  // already have this pen, skip it.
    } ಅನ್ಯಥಾ ಯದಿ ((handle = SDL_calloc(1, ಪರಿಮಾಣ(*handle))) == ರಿಕ್ತ) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;  // oh well.
    }

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    ಪೂರ್ಣಾಙ್ಕ total_buttons = 0;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < dev->ಅಂಕೆ_classes; i++) {
        ಧ್ರುವ XIAnyClassInfo *classinfo = dev->classes[i];
        ಯದಿ (classinfo->type == XIButtonClass) {
            ಧ್ರುವ XIButtonClassInfo *button_classinfo = (ಧ್ರುವ XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->ಅಂಕೆ_buttons;
        } ಅನ್ಯಥಾ ಯದಿ (classinfo->type == XIValuatorClass) {
            ಧ್ರುವ XIValuatorClassInfo *val_classinfo = (ಧ್ರುವ XIValuatorClassInfo *)classinfo;
            ಧ್ರುವ Sint8 valuator_nr = val_classinfo->ಸಂಖ್ಯೆ_2;
            ಧ್ರುವ Atom vname = val_classinfo->label;
            ಧ್ರುವ ಭಿನ್ನ min = (ಭಿನ್ನ)val_classinfo->min;
            ಧ್ರುವ ಭಿನ್ನ max = (ಭಿನ್ನ)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_ಎಣಿಕೆ;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            ಯದಿ (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } ಅನ್ಯಥಾ ಯದಿ (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } ಅನ್ಯಥಾ ಯದಿ (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } ಅನ್ಯಥಾ {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            ಯದಿ (use_this_axis) {
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

    ಧ್ರುವ bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.ಅಂಕೆ_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    ಯದಿ (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    ಯದಿ (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, ರಿಕ್ತ, &peninfo, handle, in_proximity);
    ಯದಿ (!handle->pen) {
        SDL_free(handle);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ deviceid)
{
    ಯದಿ (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &ಅಂಕೆ_device_info);
        ಯದಿ (device_info) {
            SDL_assert(ಅಂಕೆ_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            ಪ್ರತ್ಯಾಗಮ handle;
        }
    }
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಶೂನ್ಯ X11_RemovePenByDeviceID(ಪೂರ್ಣಾಙ್ಕ deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    ಯದಿ (handle) {
        SDL_RemovePenDevice(0, ರಿಕ್ತ, handle->pen);
        SDL_free(handle);
    }
}

ಶೂನ್ಯ X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    ಯದಿ (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

ಶೂನ್ಯ X11_InitPen(SDL_VideoDevice *_this)
{
    ಯದಿ (!X11_Xinput2IsInitialized()) {
        ಪ್ರತ್ಯಾಗಮ;  // we need XIQueryDevice() for this.
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
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &ಅಂಕೆ_device_info);
    ಯದಿ (device_info) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_FreePenHandle(SDL_PenID instance_id, ಶೂನ್ಯ *handle, ಶೂನ್ಯ *userdata)
{
    SDL_free(handle);
}

ಶೂನ್ಯ X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, ರಿಕ್ತ);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_XInput2NormalizePenAxes(ಧ್ರುವ X11_PenHandle *pen, ಭಿನ್ನ *coords)
{
    // Normalise axes
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ axis = 0; axis < SDL_PEN_AXIS_ಎಣಿಕೆ; ++axis) {
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ valuator = pen->valuator_for_axis[axis];
        ಯದಿ (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            ಅನುವರ್ತ;
        }

        ಭಿನ್ನ ಮೌಲ್ಯ = coords[axis];
        ಧ್ರುವ ಭಿನ್ನ min = pen->axis_min[axis];
        ಧ್ರುವ ಭಿನ್ನ max = pen->axis_max[axis];

        ಯದಿ (axis == SDL_PEN_AXIS_SLIDER) {
            ಮೌಲ್ಯ += pen->slider_bias;
        }

        // min ... 0 ... max
        ಯದಿ (min < 0.0) {
            // Normalise so that 0 remains 0.0
            ಯದಿ (ಮೌಲ್ಯ < 0) {
                ಮೌಲ್ಯ = ಮೌಲ್ಯ / (-min);
            } ಅನ್ಯಥಾ {
                ಯದಿ (max == 0.0f) {
                    ಮೌಲ್ಯ = 0.0f;
                } ಅನ್ಯಥಾ {
                    ಮೌಲ್ಯ = ಮೌಲ್ಯ / max;
                }
            }
        } ಅನ್ಯಥಾ {
            // 0 ... min ... max
            // including 0.0 = min
            ಯದಿ (max == 0.0f) {
                ಮೌಲ್ಯ = 0.0f;
            } ಅನ್ಯಥಾ {
                ಮೌಲ್ಯ = (ಮೌಲ್ಯ - min) / max;
            }
        }

        ವಿಕಲ್ಪ (axis) {
            ಪಕ್ಷ SDL_PEN_AXIS_XTILT:
            ಪಕ್ಷ SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                ಭಙ್ಗ;

            ಪಕ್ಷ SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                ಮೌಲ್ಯ *= 180.0f;
                ಮೌಲ್ಯ += pen->rotation_bias;

                // handle simple over/underflow
                ಯದಿ (ಮೌಲ್ಯ >= 180.0f) {
                    ಮೌಲ್ಯ -= 360.0f;
                } ಅನ್ಯಥಾ ಯದಿ (ಮೌಲ್ಯ < -180.0f) {
                    ಮೌಲ್ಯ += 360.0f;
                }
                ಭಙ್ಗ;

            ಸ್ವಭಾವ:
                ಭಙ್ಗ;
        }

        coords[axis] = ಮೌಲ್ಯ;
    }
}

ಶೂನ್ಯ X11_PenAxesFromValuators(ಧ್ರುವ X11_PenHandle *pen,
                              ಧ್ರುವ ದ್ವಿಗುಣ *ಒಳಹರಿವು_ಮೌಲ್ಯಗಳು, ಧ್ರುವ unsigned ವರ್ಣ *mask, ಪೂರ್ಣಾಙ್ಕ mask_len,
                              ಭಿನ್ನ axis_ಮೌಲ್ಯಗಳು[SDL_PEN_AXIS_ಎಣಿಕೆ])
{
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < SDL_PEN_AXIS_ಎಣಿಕೆ; i++) {
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ valuator = pen->valuator_for_axis[i];
        ಯದಿ ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_ಮೌಲ್ಯಗಳು[i] = 0.0f;
        } ಅನ್ಯಥಾ {
            axis_ಮೌಲ್ಯಗಳು[i] = (ಭಿನ್ನ)ಒಳಹರಿವು_ಮೌಲ್ಯಗಳು[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_ಮೌಲ್ಯಗಳು);
}

#ಅನ್ಯಥಾ

ಶೂನ್ಯ X11_InitPen(SDL_VideoDevice *_this)
{
    (ಶೂನ್ಯ) _this;
}

ಶೂನ್ಯ X11_QuitPen(SDL_VideoDevice *_this)
{
    (ಶೂನ್ಯ) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

