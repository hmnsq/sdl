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
#அந்தர்பாவ "../../SDL_internal.h"

#அந்தர்பாவ "../../events/SDL_pen_c.h"
#அந்தர்பாவ "../SDL_sysvideo.h"
#அந்தர்பாவ "SDL_x11pen.h"
#அந்தர்பாவ "SDL_x11video.h"
#அந்தர்பாவ "SDL_x11xinput2.h"

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
நிலையான bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, மாறிலி XIDeviceInfo *dev)
{
    மாறிலி SDL_VideoData *data = _this->internal;
    க்கு (முழு i = 0; i < dev->இலக்கம்_classes; i++) {
        மாறிலி XIAnyClassInfo *classinfo = dev->classes[i];
        எனில் (classinfo->type == XIValuatorClass) {
            மாறிலி XIValuatorClassInfo *val_classinfo = (மாறிலி XIValuatorClassInfo *)classinfo;
            எனில் (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                திரும்பு true;
            }
        }
    }

    திரும்பு false;
}

// Heuristically determines if device is an eraser
நிலையான bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, முழு deviceid, எழுத்து *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    எனில் (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        முழு format_return;
        unsigned long இலக்கம்_பொருட்கள்_return;
        unsigned long bytes_after_return;
        unsigned எழுத்து *tooltype_name_info = வெற்று;

        // Try Wacom-specific method
        எனில் (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &இலக்கம்_பொருட்கள்_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != வெற்று && இலக்கம்_பொருட்கள்_return > 0) {

            bool result = false;
            எழுத்து *tooltype_name = வெற்று;

            எனில் (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                எனில் (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } இல்லையெனில் எனில் (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (எழுத்து *)tooltype_name_info;
            }

            எனில் (tooltype_name) {
                எனில் (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                எனில் (tooltype_name != (எழுத்து *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                திரும்பு result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    திரும்பு (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
நிலையான size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, முழு deviceid, Atom property, Sint32 *dest, size_t max_சொற்கள்)
{
    மாறிலி SDL_VideoData *data = _this->internal;
    Atom type_return;
    முழு format_return;
    unsigned long இலக்கம்_பொருட்கள்_return;
    unsigned long bytes_after_return;
    unsigned எழுத்து *output;

    எனில் (property == None) {
        திரும்பு 0;
    }

    எனில் (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_சொற்கள், False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &இலக்கம்_பொருட்கள்_return, &bytes_after_return,
                                     &output) ||
        இலக்கம்_பொருட்கள்_return == 0 || output == வெற்று) {
        திரும்பு 0;
    }

    எனில் (type_return == XA_INTEGER) {
        முழு k;
        மாறிலி முழு to_copy = SDL_min(max_சொற்கள், இலக்கம்_பொருட்கள்_return);

        எனில் (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            க்கு (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } இல்லையெனில் எனில் (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            க்கு (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } இல்லையெனில் {
            SDL_memcpy(dest, output, அளவு(Sint32) * to_copy);
        }
        X11_XFree(output);
        திரும்பு to_copy;
    }

    திரும்பு 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
நிலையான bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, முழு deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    முழு result;

    எனில் ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        திரும்பு true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    திரும்பு false;
}

// Check if a Wacom device is in proximity of the tablet
நிலையான bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, முழு deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    எனில் (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        திரும்பு true;
    }
    திரும்பு false;
}


வகைவரை கட்டமைப்பு FindPenByDeviceIDData
{
    முழு x11_deviceid;
    வெறுமை *handle;
} FindPenByDeviceIDData;

நிலையான bool FindPenByDeviceID(வெறுமை *handle, வெறுமை *userdata)
{
    மாறிலி X11_PenHandle *x11_handle = (மாறிலி X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    எனில் (x11_handle->x11_deviceid != data->x11_deviceid) {
        திரும்பு false;
    }
    data->handle = handle;
    திரும்பு true;
}

X11_PenHandle *X11_FindPenByDeviceID(முழு deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = வெற்று;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    திரும்பு (X11_PenHandle *) data.handle;
}

நிலையான X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, மாறிலி XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = வெற்று;

    எனில் ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        திரும்பு வெற்று;  // Only track physical devices that are enabled and look like pens
    } இல்லையெனில் எனில் ((handle = X11_FindPenByDeviceID(dev->deviceid)) != வெற்று) {
        திரும்பு handle;  // already have this pen, skip it.
    } இல்லையெனில் எனில் ((handle = SDL_calloc(1, அளவு(*handle))) == வெற்று) {
        திரும்பு வெற்று;  // oh well.
    }

    க்கு (முழு i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    முழு total_buttons = 0;
    க்கு (முழு i = 0; i < dev->இலக்கம்_classes; i++) {
        மாறிலி XIAnyClassInfo *classinfo = dev->classes[i];
        எனில் (classinfo->type == XIButtonClass) {
            மாறிலி XIButtonClassInfo *button_classinfo = (மாறிலி XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->இலக்கம்_buttons;
        } இல்லையெனில் எனில் (classinfo->type == XIValuatorClass) {
            மாறிலி XIValuatorClassInfo *val_classinfo = (மாறிலி XIValuatorClassInfo *)classinfo;
            மாறிலி Sint8 valuator_nr = val_classinfo->எண்_2;
            மாறிலி Atom vname = val_classinfo->label;
            மாறிலி தசம min = (தசம)val_classinfo->min;
            மாறிலி தசம max = (தசம)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_மொத்தம்;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            எனில் (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } இல்லையெனில் எனில் (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } இல்லையெனில் எனில் (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } இல்லையெனில் {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            எனில் (use_this_axis) {
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

    மாறிலி bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.இலக்கம்_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    எனில் (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    எனில் (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, வெற்று, &peninfo, handle, in_proximity);
    எனில் (!handle->pen) {
        SDL_free(handle);
        திரும்பு வெற்று;
    }

    திரும்பு handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, முழு deviceid)
{
    எனில் (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        முழு இலக்கம்_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &இலக்கம்_device_info);
        எனில் (device_info) {
            SDL_assert(இலக்கம்_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            திரும்பு handle;
        }
    }
    திரும்பு வெற்று;
}

வெறுமை X11_RemovePenByDeviceID(முழு deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    எனில் (handle) {
        SDL_RemovePenDevice(0, வெற்று, handle->pen);
        SDL_free(handle);
    }
}

வெறுமை X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, முழு deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    எனில் (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

வெறுமை X11_InitPen(SDL_VideoDevice *_this)
{
    எனில் (!X11_Xinput2IsInitialized()) {
        திரும்பு;  // we need XIQueryDevice() for this.
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
    முழு இலக்கம்_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &இலக்கம்_device_info);
    எனில் (device_info) {
        க்கு (முழு i = 0; i < இலக்கம்_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

நிலையான வெறுமை X11_FreePenHandle(SDL_PenID instance_id, வெறுமை *handle, வெறுமை *userdata)
{
    SDL_free(handle);
}

வெறுமை X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, வெற்று);
}

நிலையான வெறுமை X11_XInput2NormalizePenAxes(மாறிலி X11_PenHandle *pen, தசம *coords)
{
    // Normalise axes
    க்கு (முழு axis = 0; axis < SDL_PEN_AXIS_மொத்தம்; ++axis) {
        மாறிலி முழு valuator = pen->valuator_for_axis[axis];
        எனில் (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            தொடர்;
        }

        தசம மதிப்பு = coords[axis];
        மாறிலி தசம min = pen->axis_min[axis];
        மாறிலி தசம max = pen->axis_max[axis];

        எனில் (axis == SDL_PEN_AXIS_SLIDER) {
            மதிப்பு += pen->slider_bias;
        }

        // min ... 0 ... max
        எனில் (min < 0.0) {
            // Normalise so that 0 remains 0.0
            எனில் (மதிப்பு < 0) {
                மதிப்பு = மதிப்பு / (-min);
            } இல்லையெனில் {
                எனில் (max == 0.0f) {
                    மதிப்பு = 0.0f;
                } இல்லையெனில் {
                    மதிப்பு = மதிப்பு / max;
                }
            }
        } இல்லையெனில் {
            // 0 ... min ... max
            // including 0.0 = min
            எனில் (max == 0.0f) {
                மதிப்பு = 0.0f;
            } இல்லையெனில் {
                மதிப்பு = (மதிப்பு - min) / max;
            }
        }

        தேர்வு (axis) {
            நிலை SDL_PEN_AXIS_XTILT:
            நிலை SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                நிறுத்து;

            நிலை SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                மதிப்பு *= 180.0f;
                மதிப்பு += pen->rotation_bias;

                // handle simple over/underflow
                எனில் (மதிப்பு >= 180.0f) {
                    மதிப்பு -= 360.0f;
                } இல்லையெனில் எனில் (மதிப்பு < -180.0f) {
                    மதிப்பு += 360.0f;
                }
                நிறுத்து;

            இயல்பு:
                நிறுத்து;
        }

        coords[axis] = மதிப்பு;
    }
}

வெறுமை X11_PenAxesFromValuators(மாறிலி X11_PenHandle *pen,
                              மாறிலி இரட்டை *உள்ளீடு_மதிப்புகள், மாறிலி unsigned எழுத்து *mask, முழு mask_len,
                              தசம axis_மதிப்புகள்[SDL_PEN_AXIS_மொத்தம்])
{
    க்கு (முழு i = 0; i < SDL_PEN_AXIS_மொத்தம்; i++) {
        மாறிலி முழு valuator = pen->valuator_for_axis[i];
        எனில் ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_மதிப்புகள்[i] = 0.0f;
        } இல்லையெனில் {
            axis_மதிப்புகள்[i] = (தசம)உள்ளீடு_மதிப்புகள்[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_மதிப்புகள்);
}

#இல்லையெனில்

வெறுமை X11_InitPen(SDL_VideoDevice *_this)
{
    (வெறுமை) _this;
}

வெறுமை X11_QuitPen(SDL_VideoDevice *_this)
{
    (வெறுமை) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

