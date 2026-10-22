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
#അന്തര്ഭാവ "../../SDL_internal.h"

#അന്തര്ഭാവ "../../events/SDL_pen_c.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "SDL_x11pen.h"
#അന്തര്ഭാവ "SDL_x11video.h"
#അന്തര്ഭാവ "SDL_x11xinput2.h"

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
സ്ഥിതം bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, സ്ഥിരം XIDeviceInfo *dev)
{
    സ്ഥിരം SDL_VideoData *data = _this->internal;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < dev->അക്കം_classes; i++) {
        സ്ഥിരം XIAnyClassInfo *classinfo = dev->classes[i];
        എങ്കിൽ (classinfo->type == XIValuatorClass) {
            സ്ഥിരം XIValuatorClassInfo *val_classinfo = (സ്ഥിരം XIValuatorClassInfo *)classinfo;
            എങ്കിൽ (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                തിരികെ true;
            }
        }
    }

    തിരികെ false;
}

// Heuristically determines if device is an eraser
സ്ഥിതം bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ deviceid, അക്ഷരം *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    എങ്കിൽ (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        പൂർണ്ണസംഖ്യ format_return;
        unsigned long അക്കം_ഇനങ്ങൾ_return;
        unsigned long bytes_after_return;
        unsigned അക്ഷരം *tooltype_name_info = ശൂന്യ;

        // Try Wacom-specific method
        എങ്കിൽ (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &അക്കം_ഇനങ്ങൾ_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != ശൂന്യ && അക്കം_ഇനങ്ങൾ_return > 0) {

            bool result = false;
            അക്ഷരം *tooltype_name = ശൂന്യ;

            എങ്കിൽ (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                എങ്കിൽ (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } അല്ലെങ്കിൽ എങ്കിൽ (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (അക്ഷരം *)tooltype_name_info;
            }

            എങ്കിൽ (tooltype_name) {
                എങ്കിൽ (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                എങ്കിൽ (tooltype_name != (അക്ഷരം *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                തിരികെ result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    തിരികെ (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
സ്ഥിതം size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ deviceid, Atom property, Sint32 *dest, size_t max_വാക്കുകൾ)
{
    സ്ഥിരം SDL_VideoData *data = _this->internal;
    Atom type_return;
    പൂർണ്ണസംഖ്യ format_return;
    unsigned long അക്കം_ഇനങ്ങൾ_return;
    unsigned long bytes_after_return;
    unsigned അക്ഷരം *output;

    എങ്കിൽ (property == None) {
        തിരികെ 0;
    }

    എങ്കിൽ (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_വാക്കുകൾ, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &അക്കം_ഇനങ്ങൾ_return, &bytes_after_return,
                                     &output) ||
        അക്കം_ഇനങ്ങൾ_return == 0 || output == ശൂന്യ) {
        തിരികെ 0;
    }

    എങ്കിൽ (type_return == XA_INTEGER) {
        പൂർണ്ണസംഖ്യ k;
        സ്ഥിരം പൂർണ്ണസംഖ്യ to_copy = SDL_min(max_വാക്കുകൾ, അക്കം_ഇനങ്ങൾ_return);

        എങ്കിൽ (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            വേണ്ടി (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } അല്ലെങ്കിൽ എങ്കിൽ (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            വേണ്ടി (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } അല്ലെങ്കിൽ {
            SDL_memcpy(dest, output, വലുപ്പം(Sint32) * to_copy);
        }
        X11_XFree(output);
        തിരികെ to_copy;
    }

    തിരികെ 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
സ്ഥിതം bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    പൂർണ്ണസംഖ്യ result;

    എങ്കിൽ ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        തിരികെ true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    തിരികെ false;
}

// Check if a Wacom device is in proximity of the tablet
സ്ഥിതം bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    എങ്കിൽ (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        തിരികെ true;
    }
    തിരികെ false;
}


തരനിർവചനം ഘടന FindPenByDeviceIDData
{
    പൂർണ്ണസംഖ്യ x11_deviceid;
    ശൂന്യം *handle;
} FindPenByDeviceIDData;

സ്ഥിതം bool FindPenByDeviceID(ശൂന്യം *handle, ശൂന്യം *userdata)
{
    സ്ഥിരം X11_PenHandle *x11_handle = (സ്ഥിരം X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    എങ്കിൽ (x11_handle->x11_deviceid != data->x11_deviceid) {
        തിരികെ false;
    }
    data->handle = handle;
    തിരികെ true;
}

X11_PenHandle *X11_FindPenByDeviceID(പൂർണ്ണസംഖ്യ deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = ശൂന്യ;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    തിരികെ (X11_PenHandle *) data.handle;
}

സ്ഥിതം X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, സ്ഥിരം XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = ശൂന്യ;

    എങ്കിൽ ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        തിരികെ ശൂന്യ;  // Only track physical devices that are enabled and look like pens
    } അല്ലെങ്കിൽ എങ്കിൽ ((handle = X11_FindPenByDeviceID(dev->deviceid)) != ശൂന്യ) {
        തിരികെ handle;  // already have this pen, skip it.
    } അല്ലെങ്കിൽ എങ്കിൽ ((handle = SDL_calloc(1, വലുപ്പം(*handle))) == ശൂന്യ) {
        തിരികെ ശൂന്യ;  // oh well.
    }

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    പൂർണ്ണസംഖ്യ total_buttons = 0;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < dev->അക്കം_classes; i++) {
        സ്ഥിരം XIAnyClassInfo *classinfo = dev->classes[i];
        എങ്കിൽ (classinfo->type == XIButtonClass) {
            സ്ഥിരം XIButtonClassInfo *button_classinfo = (സ്ഥിരം XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->അക്കം_buttons;
        } അല്ലെങ്കിൽ എങ്കിൽ (classinfo->type == XIValuatorClass) {
            സ്ഥിരം XIValuatorClassInfo *val_classinfo = (സ്ഥിരം XIValuatorClassInfo *)classinfo;
            സ്ഥിരം Sint8 valuator_nr = val_classinfo->സംഖ്യ_2;
            സ്ഥിരം Atom vname = val_classinfo->label;
            സ്ഥിരം ദശാംശം min = (ദശാംശം)val_classinfo->min;
            സ്ഥിരം ദശാംശം max = (ദശാംശം)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_എണ്ണം;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            എങ്കിൽ (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } അല്ലെങ്കിൽ എങ്കിൽ (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } അല്ലെങ്കിൽ എങ്കിൽ (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } അല്ലെങ്കിൽ {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            എങ്കിൽ (use_this_axis) {
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

    സ്ഥിരം bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.അക്കം_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    എങ്കിൽ (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    എങ്കിൽ (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, ശൂന്യ, &peninfo, handle, in_proximity);
    എങ്കിൽ (!handle->pen) {
        SDL_free(handle);
        തിരികെ ശൂന്യ;
    }

    തിരികെ handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, പൂർണ്ണസംഖ്യ deviceid)
{
    എങ്കിൽ (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        പൂർണ്ണസംഖ്യ അക്കം_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &അക്കം_device_info);
        എങ്കിൽ (device_info) {
            SDL_assert(അക്കം_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            തിരികെ handle;
        }
    }
    തിരികെ ശൂന്യ;
}

ശൂന്യം X11_RemovePenByDeviceID(പൂർണ്ണസംഖ്യ deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    എങ്കിൽ (handle) {
        SDL_RemovePenDevice(0, ശൂന്യ, handle->pen);
        SDL_free(handle);
    }
}

ശൂന്യം X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, പൂർണ്ണസംഖ്യ deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    എങ്കിൽ (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

ശൂന്യം X11_InitPen(SDL_VideoDevice *_this)
{
    എങ്കിൽ (!X11_Xinput2IsInitialized()) {
        തിരികെ;  // we need XIQueryDevice() for this.
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
    പൂർണ്ണസംഖ്യ അക്കം_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &അക്കം_device_info);
    എങ്കിൽ (device_info) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < അക്കം_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

സ്ഥിതം ശൂന്യം X11_FreePenHandle(SDL_PenID instance_id, ശൂന്യം *handle, ശൂന്യം *userdata)
{
    SDL_free(handle);
}

ശൂന്യം X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, ശൂന്യ);
}

സ്ഥിതം ശൂന്യം X11_XInput2NormalizePenAxes(സ്ഥിരം X11_PenHandle *pen, ദശാംശം *coords)
{
    // Normalise axes
    വേണ്ടി (പൂർണ്ണസംഖ്യ axis = 0; axis < SDL_PEN_AXIS_എണ്ണം; ++axis) {
        സ്ഥിരം പൂർണ്ണസംഖ്യ valuator = pen->valuator_for_axis[axis];
        എങ്കിൽ (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            തുടരുക;
        }

        ദശാംശം മൂല്യം = coords[axis];
        സ്ഥിരം ദശാംശം min = pen->axis_min[axis];
        സ്ഥിരം ദശാംശം max = pen->axis_max[axis];

        എങ്കിൽ (axis == SDL_PEN_AXIS_SLIDER) {
            മൂല്യം += pen->slider_bias;
        }

        // min ... 0 ... max
        എങ്കിൽ (min < 0.0) {
            // Normalise so that 0 remains 0.0
            എങ്കിൽ (മൂല്യം < 0) {
                മൂല്യം = മൂല്യം / (-min);
            } അല്ലെങ്കിൽ {
                എങ്കിൽ (max == 0.0f) {
                    മൂല്യം = 0.0f;
                } അല്ലെങ്കിൽ {
                    മൂല്യം = മൂല്യം / max;
                }
            }
        } അല്ലെങ്കിൽ {
            // 0 ... min ... max
            // including 0.0 = min
            എങ്കിൽ (max == 0.0f) {
                മൂല്യം = 0.0f;
            } അല്ലെങ്കിൽ {
                മൂല്യം = (മൂല്യം - min) / max;
            }
        }

        തിരഞ്ഞെടുപ്പ് (axis) {
            അവസ്ഥ SDL_PEN_AXIS_XTILT:
            അവസ്ഥ SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                നിർത്തുക;

            അവസ്ഥ SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                മൂല്യം *= 180.0f;
                മൂല്യം += pen->rotation_bias;

                // handle simple over/underflow
                എങ്കിൽ (മൂല്യം >= 180.0f) {
                    മൂല്യം -= 360.0f;
                } അല്ലെങ്കിൽ എങ്കിൽ (മൂല്യം < -180.0f) {
                    മൂല്യം += 360.0f;
                }
                നിർത്തുക;

            സ്ഥിരസ്ഥിതി:
                നിർത്തുക;
        }

        coords[axis] = മൂല്യം;
    }
}

ശൂന്യം X11_PenAxesFromValuators(സ്ഥിരം X11_PenHandle *pen,
                              സ്ഥിരം ഇരട്ട *നിവേശം_മൂല്യങ്ങൾ, സ്ഥിരം unsigned അക്ഷരം *mask, പൂർണ്ണസംഖ്യ mask_len,
                              ദശാംശം axis_മൂല്യങ്ങൾ[SDL_PEN_AXIS_എണ്ണം])
{
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < SDL_PEN_AXIS_എണ്ണം; i++) {
        സ്ഥിരം പൂർണ്ണസംഖ്യ valuator = pen->valuator_for_axis[i];
        എങ്കിൽ ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_മൂല്യങ്ങൾ[i] = 0.0f;
        } അല്ലെങ്കിൽ {
            axis_മൂല്യങ്ങൾ[i] = (ദശാംശം)നിവേശം_മൂല്യങ്ങൾ[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_മൂല്യങ്ങൾ);
}

#അല്ലെങ്കിൽ

ശൂന്യം X11_InitPen(SDL_VideoDevice *_this)
{
    (ശൂന്യം) _this;
}

ശൂന്യം X11_QuitPen(SDL_VideoDevice *_this)
{
    (ശൂന്യം) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

