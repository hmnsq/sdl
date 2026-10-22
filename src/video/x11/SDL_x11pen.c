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
#ਅਨ੍ਤਰ੍ਭਾਵ "../../SDL_internal.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_pen_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11pen.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11video.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_x11xinput2.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
ਸਥਿਰ bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, ਅਚਲ XIDeviceInfo *dev)
{
    ਅਚਲ SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਲਈ (ਪੂਰਨ i = 0; i < dev->ਅੰਕ_classes; i++) {
        ਅਚਲ XIAnyClassInfo *classinfo = dev->classes[i];
        ਜੇ (classinfo->type == XIValuatorClass) {
            ਅਚਲ XIValuatorClassInfo *val_classinfo = (ਅਚਲ XIValuatorClassInfo *)classinfo;
            ਜੇ (val_classinfo->label == ਅੰਕੜੇ->atoms.pen_atom_abs_pressure) {
                ਵਾਪਸ true;
            }
        }
    }

    ਵਾਪਸ false;
}

// Heuristically determines if device is an eraser
ਸਥਿਰ bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, ਪੂਰਨ deviceid, ਅੱਖਰ *devicename)
{
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEN_ERASER_NAME_ਟੈਗ  "eraser" // String constant to identify erasers
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਜੇ (ਅੰਕੜੇ->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        ਪੂਰਨ format_return;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਅੰਕ_ਚੀਜ਼ਾਂ_return;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਬਾਈਟਾਂ_after_return;
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *tooltype_name_info = ਨਿਰਾ;

        // Try Wacom-specific method
        ਜੇ (Success == X11_XIGetProperty(ਅੰਕੜੇ->display, deviceid,
                                         ਅੰਕੜੇ->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &ਅੰਕ_ਚੀਜ਼ਾਂ_return, &ਬਾਈਟਾਂ_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != ਨਿਰਾ && ਅੰਕ_ਚੀਜ਼ਾਂ_return > 0) {

            bool ਨਤੀਜਾ = false;
            ਅੱਖਰ *tooltype_name = ਨਿਰਾ;

            ਜੇ (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                ਜੇ (atom != None) {
                    tooltype_name = X11_XGetAtomName(ਅੰਕੜੇ->display, atom);
                }
            } ਨਹੀਂਤਾਂ ਜੇ (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (ਅੱਖਰ *)tooltype_name_info;
            }

            ਜੇ (tooltype_name) {
                ਜੇ (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_ਟੈਗ) == 0) {
                    ਨਤੀਜਾ = true;
                }
                ਜੇ (tooltype_name != (ਅੱਖਰ *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                ਵਾਪਸ ਨਤੀਜਾ;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    ਵਾਪਸ (SDL_strcasestr(devicename, PEN_ERASER_NAME_ਟੈਗ)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
ਸਥਿਰ size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, ਪੂਰਨ deviceid, Atom property, Sint32 *dest, size_t max_ਸ਼ਬਦ)
{
    ਅਚਲ SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Atom type_return;
    ਪੂਰਨ format_return;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਅੰਕ_ਚੀਜ਼ਾਂ_return;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਬਾਈਟਾਂ_after_return;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *output;

    ਜੇ (property == None) {
        ਵਾਪਸ 0;
    }

    ਜੇ (Success != X11_XIGetProperty(ਅੰਕੜੇ->display, deviceid,
                                     property,
                                     0, max_ਸ਼ਬਦ, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &ਅੰਕ_ਚੀਜ਼ਾਂ_return, &ਬਾਈਟਾਂ_after_return,
                                     &output) ||
        ਅੰਕ_ਚੀਜ਼ਾਂ_return == 0 || output == ਨਿਰਾ) {
        ਵਾਪਸ 0;
    }

    ਜੇ (type_return == XA_INTEGER) {
        ਪੂਰਨ k;
        ਅਚਲ ਪੂਰਨ ਮੰਜ਼ਿਲ_copy = SDL_min(max_ਸ਼ਬਦ, ਅੰਕ_ਚੀਜ਼ਾਂ_return);

        ਜੇ (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            ਲਈ (k = 0; k < ਮੰਜ਼ਿਲ_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ਨਹੀਂਤਾਂ ਜੇ (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            ਲਈ (k = 0; k < ਮੰਜ਼ਿਲ_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ਨਹੀਂਤਾਂ {
            SDL_memcpy(dest, output, ਆਕਾਰ(Sint32) * ਮੰਜ਼ਿਲ_copy);
        }
        X11_XFree(output);
        ਵਾਪਸ ਮੰਜ਼ਿਲ_copy;
    }

    ਵਾਪਸ 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
ਸਥਿਰ bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, ਪੂਰਨ deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Sint32 serial_id_buf[3];
    ਪੂਰਨ ਨਤੀਜਾ;

    ਜੇ ((ਨਤੀਜਾ = X11_XInput2PenGetIntProperty(_this, deviceid, ਅੰਕੜੇ->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        ਵਾਪਸ true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    ਵਾਪਸ false;
}

// Check if a Wacom device is in proximity of the tablet
ਸਥਿਰ bool X11_XInput2_Pen_Is_ਵਿੱਚ_Proximity(SDL_VideoDevice *_this, ਪੂਰਨ deviceid, bool *ਵਿੱਚ_proximity)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Sint32 serial_id_buf[5];
    ਜੇ (X11_XInput2PenGetIntProperty(_this, deviceid, ਅੰਕੜੇ->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *ਵਿੱਚ_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}


ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਲੱਭੋ_Pen_By_Device_IDData
{
    ਪੂਰਨ x11_deviceid;
    ਖਾਲੀ *handle;
} ਲੱਭੋ_Pen_By_Device_IDData;

ਸਥਿਰ bool ਲੱਭੋ_Pen_By_Device_ID(ਖਾਲੀ *handle, ਖਾਲੀ *userdata)
{
    ਅਚਲ X11_PenHandle *x11_handle = (ਅਚਲ X11_PenHandle *) handle;
    ਲੱਭੋ_Pen_By_Device_IDData *ਅੰਕੜੇ = (ਲੱਭੋ_Pen_By_Device_IDData *) userdata;
    ਜੇ (x11_handle->x11_deviceid != ਅੰਕੜੇ->x11_deviceid) {
        ਵਾਪਸ false;
    }
    ਅੰਕੜੇ->handle = handle;
    ਵਾਪਸ true;
}

X11_PenHandle *X11_ਲੱਭੋ_Pen_By_Device_ID(ਪੂਰਨ deviceid)
{
    ਲੱਭੋ_Pen_By_Device_IDData ਅੰਕੜੇ;
    ਅੰਕੜੇ.x11_deviceid = deviceid;
    ਅੰਕੜੇ.handle = ਨਿਰਾ;
    SDL_ਲੱਭੋ_Pen_By_Callback(ਲੱਭੋ_Pen_By_Device_ID, &ਅੰਕੜੇ);
    ਵਾਪਸ (X11_PenHandle *) ਅੰਕੜੇ.handle;
}

ਸਥਿਰ X11_PenHandle *X11_Maybe_ਜੋੜੋ_Pen(SDL_VideoDevice *_this, ਅਚਲ XIDeviceInfo *dev)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = ਨਿਰਾ;

    ਜੇ ((dev->use != XISlave_ਸੂਚਕ && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        ਵਾਪਸ ਨਿਰਾ;  // Only track physical devices that are enabled and look like pens
    } ਨਹੀਂਤਾਂ ਜੇ ((handle = X11_ਲੱਭੋ_Pen_By_Device_ID(dev->deviceid)) != ਨਿਰਾ) {
        ਵਾਪਸ handle;  // already have this pen, skip it.
    } ਨਹੀਂਤਾਂ ਜੇ ((handle = SDL_calloc(1, ਆਕਾਰ(*handle))) == ਨਿਰਾ) {
        ਵਾਪਸ ਨਿਰਾ;  // oh well.
    }

    ਲਈ (ਪੂਰਨ i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    ਪੂਰਨ ਕੁੱਲ_buttons = 0;
    ਲਈ (ਪੂਰਨ i = 0; i < dev->ਅੰਕ_classes; i++) {
        ਅਚਲ XIAnyClassInfo *classinfo = dev->classes[i];
        ਜੇ (classinfo->type == XIButtonClass) {
            ਅਚਲ XIButtonClassInfo *button_classinfo = (ਅਚਲ XIButtonClassInfo *)classinfo;
            ਕੁੱਲ_buttons += button_classinfo->ਅੰਕ_buttons;
        } ਨਹੀਂਤਾਂ ਜੇ (classinfo->type == XIValuatorClass) {
            ਅਚਲ XIValuatorClassInfo *val_classinfo = (ਅਚਲ XIValuatorClassInfo *)classinfo;
            ਅਚਲ Sint8 valuator_nr = val_classinfo->ਸੰਖਿਆ_2;
            ਅਚਲ Atom vname = val_classinfo->label;
            ਅਚਲ ਦਸ਼ਮਲਵ min = (ਦਸ਼ਮਲਵ)val_classinfo->min;
            ਅਚਲ ਦਸ਼ਮਲਵ max = (ਦਸ਼ਮਲਵ)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_ਗਿਣਤੀ;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            ਜੇ (vname == ਅੰਕੜੇ->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } ਨਹੀਂਤਾਂ ਜੇ (vname == ਅੰਕੜੇ->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } ਨਹੀਂਤਾਂ ਜੇ (vname == ਅੰਕੜੇ->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } ਨਹੀਂਤਾਂ {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            ਜੇ (use_this_axis) {
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

    ਅਚਲ bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.ਅੰਕ_buttons = ਕੁੱਲ_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    ਜੇ (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool ਵਿੱਚ_proximity = false;
    ਜੇ (!X11_XInput2_Pen_Is_ਵਿੱਚ_Proximity(_this, dev->deviceid, &ਵਿੱਚ_proximity)) {
        ਵਿੱਚ_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_ਜੋੜੋ_Pen_Device(0, dev->name, ਨਿਰਾ, &peninfo, handle, ਵਿੱਚ_proximity);
    ਜੇ (!handle->pen) {
        SDL_free(handle);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ handle;
}

X11_PenHandle *X11_Maybe_ਜੋੜੋ_Pen_By_Device_ID(SDL_VideoDevice *_this, ਪੂਰਨ deviceid)
{
    ਜੇ (X11_Xinput2IsInitialized()) {
        SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
        ਪੂਰਨ ਅੰਕ_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(ਅੰਕੜੇ->display, deviceid, &ਅੰਕ_device_info);
        ਜੇ (device_info) {
            SDL_assert(ਅੰਕ_device_info == 1);
            X11_PenHandle *handle = X11_Maybe_ਜੋੜੋ_Pen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            ਵਾਪਸ handle;
        }
    }
    ਵਾਪਸ ਨਿਰਾ;
}

ਖਾਲੀ X11_RemovePenByDeviceID(ਪੂਰਨ deviceid)
{
    X11_PenHandle *handle = X11_ਲੱਭੋ_Pen_By_Device_ID(deviceid);
    ਜੇ (handle) {
        SDL_RemovePenDevice(0, ਨਿਰਾ, handle->pen);
        SDL_free(handle);
    }
}

ਖਾਲੀ X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ deviceid)
{
    bool ਵਿੱਚ_proximity;
    X11_PenHandle *pen = X11_ਲੱਭੋ_Pen_By_Device_ID(deviceid);
    ਜੇ (pen && X11_XInput2_Pen_Is_ਵਿੱਚ_Proximity(_this, deviceid, &ਵਿੱਚ_proximity)) {
        SDL_SendPenProximity(0, pen->pen, ਖਿੜਕੀ, ਵਿੱਚ_proximity, ਵਿੱਚ_proximity);
    }
}

ਖਾਲੀ X11_InitPen(SDL_VideoDevice *_this)
{
    ਜੇ (!X11_Xinput2IsInitialized()) {
        ਵਾਪਸ;  // we need XIQueryDevice() for this.
    }

    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LOOKUP_PEN_ATOM(X) X11_XInternAtom(ਅੰਕੜੇ->display, X, False)
    ਅੰਕੜੇ->atoms.pen_atom_device_ਗੁਣਨਫਲ_id = LOOKUP_PEN_ATOM("Device Product ID");
    ਅੰਕੜੇ->atoms.pen_atom_wacom_serial_ids = LOOKUP_PEN_ATOM("Wacom Serial IDs");
    ਅੰਕੜੇ->atoms.pen_atom_wacom_tool_type = LOOKUP_PEN_ATOM("Wacom Tool Type");
    ਅੰਕੜੇ->atoms.pen_atom_abs_pressure = LOOKUP_PEN_ATOM("Abs Pressure");
    ਅੰਕੜੇ->atoms.pen_atom_abs_tilt_x = LOOKUP_PEN_ATOM("Abs Tilt X");
    ਅੰਕੜੇ->atoms.pen_atom_abs_tilt_y = LOOKUP_PEN_ATOM("Abs Tilt Y");
    #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ LOOKUP_PEN_ATOM

    // Do an initial check on devices. After this, we'll add/remove individual pens when XI_HierarchyChanged events alert us.
    ਪੂਰਨ ਅੰਕ_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(ਅੰਕੜੇ->display, XIAllDevices, &ਅੰਕ_device_info);
    ਜੇ (device_info) {
        ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕ_device_info; i++) {
            X11_Maybe_ਜੋੜੋ_Pen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

ਸਥਿਰ ਖਾਲੀ X11_FreePenHandle(SDL_PenID instance_id, ਖਾਲੀ *handle, ਖਾਲੀ *userdata)
{
    SDL_free(handle);
}

ਖਾਲੀ X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, ਨਿਰਾ);
}

ਸਥਿਰ ਖਾਲੀ X11_XInput2NormalizePenAxes(ਅਚਲ X11_PenHandle *pen, ਦਸ਼ਮਲਵ *coords)
{
    // Normalise axes
    ਲਈ (ਪੂਰਨ axis = 0; axis < SDL_PEN_AXIS_ਗਿਣਤੀ; ++axis) {
        ਅਚਲ ਪੂਰਨ valuator = pen->valuator_for_axis[axis];
        ਜੇ (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            ਜਾਰੀ;
        }

        ਦਸ਼ਮਲਵ ਮੁੱਲ = coords[axis];
        ਅਚਲ ਦਸ਼ਮਲਵ min = pen->axis_min[axis];
        ਅਚਲ ਦਸ਼ਮਲਵ max = pen->axis_max[axis];

        ਜੇ (axis == SDL_PEN_AXIS_SLIDER) {
            ਮੁੱਲ += pen->slider_bias;
        }

        // min ... 0 ... max
        ਜੇ (min < 0.0) {
            // Normalise so that 0 remains 0.0
            ਜੇ (ਮੁੱਲ < 0) {
                ਮੁੱਲ = ਮੁੱਲ / (-min);
            } ਨਹੀਂਤਾਂ {
                ਜੇ (max == 0.0f) {
                    ਮੁੱਲ = 0.0f;
                } ਨਹੀਂਤਾਂ {
                    ਮੁੱਲ = ਮੁੱਲ / max;
                }
            }
        } ਨਹੀਂਤਾਂ {
            // 0 ... min ... max
            // including 0.0 = min
            ਜੇ (max == 0.0f) {
                ਮੁੱਲ = 0.0f;
            } ਨਹੀਂਤਾਂ {
                ਮੁੱਲ = (ਮੁੱਲ - min) / max;
            }
        }

        ਚੋਣ (axis) {
            ਹਾਲਤ SDL_PEN_AXIS_XTILT:
            ਹਾਲਤ SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                ਰੋਕੋ;

            ਹਾਲਤ SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                ਮੁੱਲ *= 180.0f;
                ਮੁੱਲ += pen->rotation_bias;

                // handle simple over/underflow
                ਜੇ (ਮੁੱਲ >= 180.0f) {
                    ਮੁੱਲ -= 360.0f;
                } ਨਹੀਂਤਾਂ ਜੇ (ਮੁੱਲ < -180.0f) {
                    ਮੁੱਲ += 360.0f;
                }
                ਰੋਕੋ;

            ਮੂਲ:
                ਰੋਕੋ;
        }

        coords[axis] = ਮੁੱਲ;
    }
}

ਖਾਲੀ X11_PenAxesFromValuators(ਅਚਲ X11_PenHandle *pen,
                              ਅਚਲ ਦੁੱਗਣਾ *ਨਿਵੇਸ਼_ਮੁੱਲਾਂ, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਨਕਾਬ, ਪੂਰਨ ਨਕਾਬ_len,
                              ਦਸ਼ਮਲਵ axis_ਮੁੱਲਾਂ[SDL_PEN_AXIS_ਗਿਣਤੀ])
{
    ਲਈ (ਪੂਰਨ i = 0; i < SDL_PEN_AXIS_ਗਿਣਤੀ; i++) {
        ਅਚਲ ਪੂਰਨ valuator = pen->valuator_for_axis[i];
        ਜੇ ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= ਨਕਾਬ_len * 8) || !(XIMask_Is_ਸੈੱਟ(ਨਕਾਬ, valuator))) {
            axis_ਮੁੱਲਾਂ[i] = 0.0f;
        } ਨਹੀਂਤਾਂ {
            axis_ਮੁੱਲਾਂ[i] = (ਦਸ਼ਮਲਵ)ਨਿਵੇਸ਼_ਮੁੱਲਾਂ[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_ਮੁੱਲਾਂ);
}

#ਨਹੀਂਤਾਂ

ਖਾਲੀ X11_InitPen(SDL_VideoDevice *_this)
{
    (ਖਾਲੀ) _this;
}

ਖਾਲੀ X11_QuitPen(SDL_VideoDevice *_this)
{
    (ਖਾਲੀ) _this;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_X11_XINPUT2

