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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
ಸ್ಥಿರ bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ XIDeviceInfo *dev)
{
    ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < dev->ಅಂಕೆ_classes; i++) {
        ಸ್ಥಿರಾಂಕ XIAnyClassInfo *classinfo = dev->classes[i];
        ಆದರೆ (classinfo->type == XIValuatorClass) {
            ಸ್ಥಿರಾಂಕ XIValuatorClassInfo *val_classinfo = (ಸ್ಥಿರಾಂಕ XIValuatorClassInfo *)classinfo;
            ಆದರೆ (val_classinfo->label == ದತ್ತಾಂಶ->atoms.pen_atom_abs_pressure) {
                ಹಿಂತಿರುಗಿ true;
            }
        }
    }

    ಹಿಂತಿರುಗಿ false;
}

// Heuristically determines if device is an eraser
ಸ್ಥಿರ bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ deviceid, ಅಕ್ಷರ *devicename)
{
    #ವ್ಯಾಖ್ಯಾನಿಸು PEN_ERASER_NAME_ಟ್ಯಾಗ್  "eraser" // String constant to identify erasers
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ಆದರೆ (ದತ್ತಾಂಶ->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        ಪೂರ್ಣಾಂಕ format_return;
        ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಅಂಕೆ_ವಸ್ತುಗಳು_return;
        ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಬೈಟುಗಳು_after_return;
        ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *tooltype_name_info = ಖಾಲಿ;

        // Try Wacom-specific method
        ಆದರೆ (Success == X11_XIGetProperty(ದತ್ತಾಂಶ->display, deviceid,
                                         ದತ್ತಾಂಶ->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &ಅಂಕೆ_ವಸ್ತುಗಳು_return, &ಬೈಟುಗಳು_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != ಖಾಲಿ && ಅಂಕೆ_ವಸ್ತುಗಳು_return > 0) {

            bool ಫಲಿತಾಂಶ = false;
            ಅಕ್ಷರ *tooltype_name = ಖಾಲಿ;

            ಆದರೆ (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                ಆದರೆ (atom != None) {
                    tooltype_name = X11_XGetAtomName(ದತ್ತಾಂಶ->display, atom);
                }
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (ಅಕ್ಷರ *)tooltype_name_info;
            }

            ಆದರೆ (tooltype_name) {
                ಆದರೆ (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_ಟ್ಯಾಗ್) == 0) {
                    ಫಲಿತಾಂಶ = true;
                }
                ಆದರೆ (tooltype_name != (ಅಕ್ಷರ *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    ಹಿಂತಿರುಗಿ (SDL_strcasestr(devicename, PEN_ERASER_NAME_ಟ್ಯಾಗ್)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
ಸ್ಥಿರ size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ deviceid, Atom property, Sint32 *dest, size_t max_ಪದಗಳು)
{
    ಸ್ಥಿರಾಂಕ SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Atom type_return;
    ಪೂರ್ಣಾಂಕ format_return;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಅಂಕೆ_ವಸ್ತುಗಳು_return;
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಬೈಟುಗಳು_after_return;
    ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *output;

    ಆದರೆ (property == None) {
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (Success != X11_XIGetProperty(ದತ್ತಾಂಶ->display, deviceid,
                                     property,
                                     0, max_ಪದಗಳು, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &ಅಂಕೆ_ವಸ್ತುಗಳು_return, &ಬೈಟುಗಳು_after_return,
                                     &output) ||
        ಅಂಕೆ_ವಸ್ತುಗಳು_return == 0 || output == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (type_return == XA_INTEGER) {
        ಪೂರ್ಣಾಂಕ k;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಗಮ್ಯ_copy = SDL_min(max_ಪದಗಳು, ಅಂಕೆ_ವಸ್ತುಗಳು_return);

        ಆದರೆ (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            ಗಾಗಿ (k = 0; k < ಗಮ್ಯ_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            ಗಾಗಿ (k = 0; k < ಗಮ್ಯ_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_memcpy(dest, output, ಗಾತ್ರ(Sint32) * ಗಮ್ಯ_copy);
        }
        X11_XFree(output);
        ಹಿಂತಿರುಗಿ ಗಮ್ಯ_copy;
    }

    ಹಿಂತಿರುಗಿ 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
ಸ್ಥಿರ bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Sint32 serial_id_buf[3];
    ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ;

    ಆದರೆ ((ಫಲಿತಾಂಶ = X11_XInput2PenGetIntProperty(_this, deviceid, ದತ್ತಾಂಶ->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        ಹಿಂತಿರುಗಿ true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    ಹಿಂತಿರುಗಿ false;
}

// Check if a Wacom device is in proximity of the tablet
ಸ್ಥಿರ bool X11_XInput2_Pen_Is_ಒಳ_Proximity(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ deviceid, bool *ಒಳ_proximity)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Sint32 serial_id_buf[5];
    ಆದರೆ (X11_XInput2PenGetIntProperty(_this, deviceid, ದತ್ತಾಂಶ->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *ಒಳ_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}


ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಕಂಡುಹಿಡಿ_Pen_By_Device_IDData
{
    ಪೂರ್ಣಾಂಕ x11_deviceid;
    ಶೂನ್ಯ *handle;
} ಕಂಡುಹಿಡಿ_Pen_By_Device_IDData;

ಸ್ಥಿರ bool ಕಂಡುಹಿಡಿ_Pen_By_Device_ID(ಶೂನ್ಯ *handle, ಶೂನ್ಯ *userdata)
{
    ಸ್ಥಿರಾಂಕ X11_PenHandle *x11_handle = (ಸ್ಥಿರಾಂಕ X11_PenHandle *) handle;
    ಕಂಡುಹಿಡಿ_Pen_By_Device_IDData *ದತ್ತಾಂಶ = (ಕಂಡುಹಿಡಿ_Pen_By_Device_IDData *) userdata;
    ಆದರೆ (x11_handle->x11_deviceid != ದತ್ತಾಂಶ->x11_deviceid) {
        ಹಿಂತಿರುಗಿ false;
    }
    ದತ್ತಾಂಶ->handle = handle;
    ಹಿಂತಿರುಗಿ true;
}

X11_PenHandle *X11_ಕಂಡುಹಿಡಿ_Pen_By_Device_ID(ಪೂರ್ಣಾಂಕ deviceid)
{
    ಕಂಡುಹಿಡಿ_Pen_By_Device_IDData ದತ್ತಾಂಶ;
    ದತ್ತಾಂಶ.x11_deviceid = deviceid;
    ದತ್ತಾಂಶ.handle = ಖಾಲಿ;
    SDL_ಕಂಡುಹಿಡಿ_Pen_By_Callback(ಕಂಡುಹಿಡಿ_Pen_By_Device_ID, &ದತ್ತಾಂಶ);
    ಹಿಂತಿರುಗಿ (X11_PenHandle *) ದತ್ತಾಂಶ.handle;
}

ಸ್ಥಿರ X11_PenHandle *X11_Maybe_ಕೂಡಿಸು_Pen(SDL_VideoDevice *_this, ಸ್ಥಿರಾಂಕ XIDeviceInfo *dev)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = ಖಾಲಿ;

    ಆದರೆ ((dev->use != XISlave_ಸೂಚಕ && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;  // Only track physical devices that are enabled and look like pens
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((handle = X11_ಕಂಡುಹಿಡಿ_Pen_By_Device_ID(dev->deviceid)) != ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ handle;  // already have this pen, skip it.
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((handle = SDL_calloc(1, ಗಾತ್ರ(*handle))) == ಖಾಲಿ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;  // oh well.
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    ಪೂರ್ಣಾಂಕ ಒಟ್ಟು_buttons = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < dev->ಅಂಕೆ_classes; i++) {
        ಸ್ಥಿರಾಂಕ XIAnyClassInfo *classinfo = dev->classes[i];
        ಆದರೆ (classinfo->type == XIButtonClass) {
            ಸ್ಥಿರಾಂಕ XIButtonClassInfo *button_classinfo = (ಸ್ಥಿರಾಂಕ XIButtonClassInfo *)classinfo;
            ಒಟ್ಟು_buttons += button_classinfo->ಅಂಕೆ_buttons;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (classinfo->type == XIValuatorClass) {
            ಸ್ಥಿರಾಂಕ XIValuatorClassInfo *val_classinfo = (ಸ್ಥಿರಾಂಕ XIValuatorClassInfo *)classinfo;
            ಸ್ಥಿರಾಂಕ Sint8 valuator_nr = val_classinfo->ಸಂಖ್ಯೆ_2;
            ಸ್ಥಿರಾಂಕ Atom vname = val_classinfo->label;
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ min = (ದಶಮಾಂಶ)val_classinfo->min;
            ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ max = (ದಶಮಾಂಶ)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_ಎಣಿಕೆ;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            ಆದರೆ (vname == ದತ್ತಾಂಶ->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (vname == ದತ್ತಾಂಶ->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (vname == ದತ್ತಾಂಶ->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } ಇಲ್ಲದಿದ್ದರೆ {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            ಆದರೆ (use_this_axis) {
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

    ಸ್ಥಿರಾಂಕ bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.ಅಂಕೆ_buttons = ಒಟ್ಟು_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    ಆದರೆ (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool ಒಳ_proximity = false;
    ಆದರೆ (!X11_XInput2_Pen_Is_ಒಳ_Proximity(_this, dev->deviceid, &ಒಳ_proximity)) {
        ಒಳ_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_ಕೂಡಿಸು_Pen_Device(0, dev->name, ಖಾಲಿ, &peninfo, handle, ಒಳ_proximity);
    ಆದರೆ (!handle->pen) {
        SDL_free(handle);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ handle;
}

X11_PenHandle *X11_Maybe_ಕೂಡಿಸು_Pen_By_Device_ID(SDL_VideoDevice *_this, ಪೂರ್ಣಾಂಕ deviceid)
{
    ಆದರೆ (X11_Xinput2IsInitialized()) {
        SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
        ಪೂರ್ಣಾಂಕ ಅಂಕೆ_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(ದತ್ತಾಂಶ->display, deviceid, &ಅಂಕೆ_device_info);
        ಆದರೆ (device_info) {
            SDL_assert(ಅಂಕೆ_device_info == 1);
            X11_PenHandle *handle = X11_Maybe_ಕೂಡಿಸು_Pen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            ಹಿಂತಿರುಗಿ handle;
        }
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಶೂನ್ಯ X11_RemovePenByDeviceID(ಪೂರ್ಣಾಂಕ deviceid)
{
    X11_PenHandle *handle = X11_ಕಂಡುಹಿಡಿ_Pen_By_Device_ID(deviceid);
    ಆದರೆ (handle) {
        SDL_RemovePenDevice(0, ಖಾಲಿ, handle->pen);
        SDL_free(handle);
    }
}

ಶೂನ್ಯ X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ಪೂರ್ಣಾಂಕ deviceid)
{
    bool ಒಳ_proximity;
    X11_PenHandle *pen = X11_ಕಂಡುಹಿಡಿ_Pen_By_Device_ID(deviceid);
    ಆದರೆ (pen && X11_XInput2_Pen_Is_ಒಳ_Proximity(_this, deviceid, &ಒಳ_proximity)) {
        SDL_SendPenProximity(0, pen->pen, ಕಿಟಕಿ, ಒಳ_proximity, ಒಳ_proximity);
    }
}

ಶೂನ್ಯ X11_InitPen(SDL_VideoDevice *_this)
{
    ಆದರೆ (!X11_Xinput2IsInitialized()) {
        ಹಿಂತಿರುಗಿ;  // we need XIQueryDevice() for this.
    }

    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    #ವ್ಯಾಖ್ಯಾನಿಸು LOOKUP_PEN_ATOM(X) X11_XInternAtom(ದತ್ತಾಂಶ->display, X, False)
    ದತ್ತಾಂಶ->atoms.pen_atom_device_ಗುಣಲಬ್ಧ_id = LOOKUP_PEN_ATOM("Device Product ID");
    ದತ್ತಾಂಶ->atoms.pen_atom_wacom_serial_ids = LOOKUP_PEN_ATOM("Wacom Serial IDs");
    ದತ್ತಾಂಶ->atoms.pen_atom_wacom_tool_type = LOOKUP_PEN_ATOM("Wacom Tool Type");
    ದತ್ತಾಂಶ->atoms.pen_atom_abs_pressure = LOOKUP_PEN_ATOM("Abs Pressure");
    ದತ್ತಾಂಶ->atoms.pen_atom_abs_tilt_x = LOOKUP_PEN_ATOM("Abs Tilt X");
    ದತ್ತಾಂಶ->atoms.pen_atom_abs_tilt_y = LOOKUP_PEN_ATOM("Abs Tilt Y");
    #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು LOOKUP_PEN_ATOM

    // Do an initial check on devices. After this, we'll add/remove individual pens when XI_HierarchyChanged events alert us.
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(ದತ್ತಾಂಶ->display, XIAllDevices, &ಅಂಕೆ_device_info);
    ಆದರೆ (device_info) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಂಕೆ_device_info; i++) {
            X11_Maybe_ಕೂಡಿಸು_Pen(_this, &device_info[i]);
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
    SDL_RemoveAllPenDevices(X11_FreePenHandle, ಖಾಲಿ);
}

ಸ್ಥಿರ ಶೂನ್ಯ X11_XInput2NormalizePenAxes(ಸ್ಥಿರಾಂಕ X11_PenHandle *pen, ದಶಮಾಂಶ *coords)
{
    // Normalise axes
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ axis = 0; axis < SDL_PEN_AXIS_ಎಣಿಕೆ; ++axis) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ valuator = pen->valuator_for_axis[axis];
        ಆದರೆ (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            ಮುಂದುವರಿ;
        }

        ದಶಮಾಂಶ ಮೌಲ್ಯ = coords[axis];
        ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ min = pen->axis_min[axis];
        ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ max = pen->axis_max[axis];

        ಆದರೆ (axis == SDL_PEN_AXIS_SLIDER) {
            ಮೌಲ್ಯ += pen->slider_bias;
        }

        // min ... 0 ... max
        ಆದರೆ (min < 0.0) {
            // Normalise so that 0 remains 0.0
            ಆದರೆ (ಮೌಲ್ಯ < 0) {
                ಮೌಲ್ಯ = ಮೌಲ್ಯ / (-min);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಆದರೆ (max == 0.0f) {
                    ಮೌಲ್ಯ = 0.0f;
                } ಇಲ್ಲದಿದ್ದರೆ {
                    ಮೌಲ್ಯ = ಮೌಲ್ಯ / max;
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            // 0 ... min ... max
            // including 0.0 = min
            ಆದರೆ (max == 0.0f) {
                ಮೌಲ್ಯ = 0.0f;
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಮೌಲ್ಯ = (ಮೌಲ್ಯ - min) / max;
            }
        }

        ಆಯ್ಕೆ (axis) {
            ಸ್ಥಿತಿ SDL_PEN_AXIS_XTILT:
            ಸ್ಥಿತಿ SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                ನಿಲ್ಲಿಸು;

            ಸ್ಥಿತಿ SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                ಮೌಲ್ಯ *= 180.0f;
                ಮೌಲ್ಯ += pen->rotation_bias;

                // handle simple over/underflow
                ಆದರೆ (ಮೌಲ್ಯ >= 180.0f) {
                    ಮೌಲ್ಯ -= 360.0f;
                } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಮೌಲ್ಯ < -180.0f) {
                    ಮೌಲ್ಯ += 360.0f;
                }
                ನಿಲ್ಲಿಸು;

            ಪೂರ್ವನಿಯೋಜಿತ:
                ನಿಲ್ಲಿಸು;
        }

        coords[axis] = ಮೌಲ್ಯ;
    }
}

ಶೂನ್ಯ X11_PenAxesFromValuators(ಸ್ಥಿರಾಂಕ X11_PenHandle *pen,
                              ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ *ಒಳಹರಿವು_ಮೌಲ್ಯಗಳು, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ಮುಖವಾಡ, ಪೂರ್ಣಾಂಕ ಮುಖವಾಡ_len,
                              ದಶಮಾಂಶ axis_ಮೌಲ್ಯಗಳು[SDL_PEN_AXIS_ಎಣಿಕೆ])
{
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < SDL_PEN_AXIS_ಎಣಿಕೆ; i++) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ valuator = pen->valuator_for_axis[i];
        ಆದರೆ ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= ಮುಖವಾಡ_len * 8) || !(XIMask_Is_ಗಣ(ಮುಖವಾಡ, valuator))) {
            axis_ಮೌಲ್ಯಗಳು[i] = 0.0f;
        } ಇಲ್ಲದಿದ್ದರೆ {
            axis_ಮೌಲ್ಯಗಳು[i] = (ದಶಮಾಂಶ)ಒಳಹರಿವು_ಮೌಲ್ಯಗಳು[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_ಮೌಲ್ಯಗಳು);
}

#ಇಲ್ಲದಿದ್ದರೆ

ಶೂನ್ಯ X11_InitPen(SDL_VideoDevice *_this)
{
    (ಶೂನ್ಯ) _this;
}

ಶೂನ್ಯ X11_QuitPen(SDL_VideoDevice *_this)
{
    (ಶೂನ್ಯ) _this;
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_X11_XINPUT2

