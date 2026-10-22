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
#अन्तर्भाव "../../SDL_internal.h"

#अन्तर्भाव "../../events/SDL_pen_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_x11pen.h"
#अन्तर्भाव "SDL_x11video.h"
#अन्तर्भाव "SDL_x11xinput2.h"

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
स्थिर bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, ध्रुव XIDeviceInfo *dev)
{
    ध्रुव SDL_VideoData *data = _this->internal;
    प्रति (पूर्णाङ्क i = 0; i < dev->अंक_classes; i++) {
        ध्रुव XIAnyClassInfo *classinfo = dev->classes[i];
        यदि (classinfo->type == XIValuatorClass) {
            ध्रुव XIValuatorClassInfo *val_classinfo = (ध्रुव XIValuatorClassInfo *)classinfo;
            यदि (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                प्रत्यागम true;
            }
        }
    }

    प्रत्यागम false;
}

// Heuristically determines if device is an eraser
स्थिर bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, वर्ण *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    यदि (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        पूर्णाङ्क format_return;
        unsigned long अंक_वस्तुएँ_return;
        unsigned long bytes_after_return;
        unsigned वर्ण *tooltype_name_info = रिक्त;

        // Try Wacom-specific method
        यदि (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &अंक_वस्तुएँ_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != रिक्त && अंक_वस्तुएँ_return > 0) {

            bool result = false;
            वर्ण *tooltype_name = रिक्त;

            यदि (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                यदि (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } अन्यथा यदि (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (वर्ण *)tooltype_name_info;
            }

            यदि (tooltype_name) {
                यदि (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                यदि (tooltype_name != (वर्ण *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                प्रत्यागम result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    प्रत्यागम (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
स्थिर size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, Atom property, Sint32 *dest, size_t max_शब्दगण)
{
    ध्रुव SDL_VideoData *data = _this->internal;
    Atom type_return;
    पूर्णाङ्क format_return;
    unsigned long अंक_वस्तुएँ_return;
    unsigned long bytes_after_return;
    unsigned वर्ण *output;

    यदि (property == None) {
        प्रत्यागम 0;
    }

    यदि (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_शब्दगण, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &अंक_वस्तुएँ_return, &bytes_after_return,
                                     &output) ||
        अंक_वस्तुएँ_return == 0 || output == रिक्त) {
        प्रत्यागम 0;
    }

    यदि (type_return == XA_INTEGER) {
        पूर्णाङ्क k;
        ध्रुव पूर्णाङ्क to_copy = SDL_min(max_शब्दगण, अंक_वस्तुएँ_return);

        यदि (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            प्रति (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा यदि (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            प्रति (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा {
            SDL_memcpy(dest, output, परिमाण(Sint32) * to_copy);
        }
        X11_XFree(output);
        प्रत्यागम to_copy;
    }

    प्रत्यागम 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
स्थिर bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    पूर्णाङ्क result;

    यदि ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        प्रत्यागम true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    प्रत्यागम false;
}

// Check if a Wacom device is in proximity of the tablet
स्थिर bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    यदि (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        प्रत्यागम true;
    }
    प्रत्यागम false;
}


प्रकारनिर्देश संरचना FindPenByDeviceIDData
{
    पूर्णाङ्क x11_deviceid;
    शून्य *handle;
} FindPenByDeviceIDData;

स्थिर bool FindPenByDeviceID(शून्य *handle, शून्य *userdata)
{
    ध्रुव X11_PenHandle *x11_handle = (ध्रुव X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    यदि (x11_handle->x11_deviceid != data->x11_deviceid) {
        प्रत्यागम false;
    }
    data->handle = handle;
    प्रत्यागम true;
}

X11_PenHandle *X11_FindPenByDeviceID(पूर्णाङ्क deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = रिक्त;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    प्रत्यागम (X11_PenHandle *) data.handle;
}

स्थिर X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, ध्रुव XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = रिक्त;

    यदि ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        प्रत्यागम रिक्त;  // Only track physical devices that are enabled and look like pens
    } अन्यथा यदि ((handle = X11_FindPenByDeviceID(dev->deviceid)) != रिक्त) {
        प्रत्यागम handle;  // already have this pen, skip it.
    } अन्यथा यदि ((handle = SDL_calloc(1, परिमाण(*handle))) == रिक्त) {
        प्रत्यागम रिक्त;  // oh well.
    }

    प्रति (पूर्णाङ्क i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    पूर्णाङ्क total_buttons = 0;
    प्रति (पूर्णाङ्क i = 0; i < dev->अंक_classes; i++) {
        ध्रुव XIAnyClassInfo *classinfo = dev->classes[i];
        यदि (classinfo->type == XIButtonClass) {
            ध्रुव XIButtonClassInfo *button_classinfo = (ध्रुव XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->अंक_buttons;
        } अन्यथा यदि (classinfo->type == XIValuatorClass) {
            ध्रुव XIValuatorClassInfo *val_classinfo = (ध्रुव XIValuatorClassInfo *)classinfo;
            ध्रुव Sint8 valuator_nr = val_classinfo->संख्या_2;
            ध्रुव Atom vname = val_classinfo->label;
            ध्रुव भिन्न min = (भिन्न)val_classinfo->min;
            ध्रुव भिन्न max = (भिन्न)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_गिनती;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            यदि (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } अन्यथा यदि (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } अन्यथा यदि (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } अन्यथा {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            यदि (use_this_axis) {
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

    ध्रुव bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.अंक_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    यदि (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    यदि (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, रिक्त, &peninfo, handle, in_proximity);
    यदि (!handle->pen) {
        SDL_free(handle);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, पूर्णाङ्क deviceid)
{
    यदि (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        पूर्णाङ्क अंक_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &अंक_device_info);
        यदि (device_info) {
            SDL_assert(अंक_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            प्रत्यागम handle;
        }
    }
    प्रत्यागम रिक्त;
}

शून्य X11_RemovePenByDeviceID(पूर्णाङ्क deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    यदि (handle) {
        SDL_RemovePenDevice(0, रिक्त, handle->pen);
        SDL_free(handle);
    }
}

शून्य X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, पूर्णाङ्क deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    यदि (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

शून्य X11_InitPen(SDL_VideoDevice *_this)
{
    यदि (!X11_Xinput2IsInitialized()) {
        प्रत्यागम;  // we need XIQueryDevice() for this.
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
    पूर्णाङ्क अंक_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &अंक_device_info);
    यदि (device_info) {
        प्रति (पूर्णाङ्क i = 0; i < अंक_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

स्थिर शून्य X11_FreePenHandle(SDL_PenID instance_id, शून्य *handle, शून्य *userdata)
{
    SDL_free(handle);
}

शून्य X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, रिक्त);
}

स्थिर शून्य X11_XInput2NormalizePenAxes(ध्रुव X11_PenHandle *pen, भिन्न *coords)
{
    // Normalise axes
    प्रति (पूर्णाङ्क axis = 0; axis < SDL_PEN_AXIS_गिनती; ++axis) {
        ध्रुव पूर्णाङ्क valuator = pen->valuator_for_axis[axis];
        यदि (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            अनुवर्त;
        }

        भिन्न मूल्य = coords[axis];
        ध्रुव भिन्न min = pen->axis_min[axis];
        ध्रुव भिन्न max = pen->axis_max[axis];

        यदि (axis == SDL_PEN_AXIS_SLIDER) {
            मूल्य += pen->slider_bias;
        }

        // min ... 0 ... max
        यदि (min < 0.0) {
            // Normalise so that 0 remains 0.0
            यदि (मूल्य < 0) {
                मूल्य = मूल्य / (-min);
            } अन्यथा {
                यदि (max == 0.0f) {
                    मूल्य = 0.0f;
                } अन्यथा {
                    मूल्य = मूल्य / max;
                }
            }
        } अन्यथा {
            // 0 ... min ... max
            // including 0.0 = min
            यदि (max == 0.0f) {
                मूल्य = 0.0f;
            } अन्यथा {
                मूल्य = (मूल्य - min) / max;
            }
        }

        विकल्प (axis) {
            पक्ष SDL_PEN_AXIS_XTILT:
            पक्ष SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                भङ्ग;

            पक्ष SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                मूल्य *= 180.0f;
                मूल्य += pen->rotation_bias;

                // handle simple over/underflow
                यदि (मूल्य >= 180.0f) {
                    मूल्य -= 360.0f;
                } अन्यथा यदि (मूल्य < -180.0f) {
                    मूल्य += 360.0f;
                }
                भङ्ग;

            स्वभाव:
                भङ्ग;
        }

        coords[axis] = मूल्य;
    }
}

शून्य X11_PenAxesFromValuators(ध्रुव X11_PenHandle *pen,
                              ध्रुव द्विगुण *निवेश_मूल्यावली, ध्रुव unsigned वर्ण *mask, पूर्णाङ्क mask_len,
                              भिन्न axis_मूल्यावली[SDL_PEN_AXIS_गिनती])
{
    प्रति (पूर्णाङ्क i = 0; i < SDL_PEN_AXIS_गिनती; i++) {
        ध्रुव पूर्णाङ्क valuator = pen->valuator_for_axis[i];
        यदि ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_मूल्यावली[i] = 0.0f;
        } अन्यथा {
            axis_मूल्यावली[i] = (भिन्न)निवेश_मूल्यावली[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_मूल्यावली);
}

#अन्यथा

शून्य X11_InitPen(SDL_VideoDevice *_this)
{
    (शून्य) _this;
}

शून्य X11_QuitPen(SDL_VideoDevice *_this)
{
    (शून्य) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

