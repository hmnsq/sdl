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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
स्थिर bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, ध्रुव XIDeviceInfo *dev)
{
    ध्रुव SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    प्रति (पूर्णाङ्क i = 0; i < dev->अङ्कः_classes; i++) {
        ध्रुव XIAnyClassInfo *classinfo = dev->classes[i];
        यदि (classinfo->type == XIValuatorClass) {
            ध्रुव XIValuatorClassInfo *val_classinfo = (ध्रुव XIValuatorClassInfo *)classinfo;
            यदि (val_classinfo->label == दत्त->atoms.pen_atom_abs_pressure) {
                प्रत्यागम true;
            }
        }
    }

    प्रत्यागम false;
}

// Heuristically determines if device is an eraser
स्थिर bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, वर्ण *devicename)
{
    #परिभाषय PEN_ERASER_NAME_चिह्नकम्  "eraser" // String constant to identify erasers
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    यदि (दत्त->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        पूर्णाङ्क format_return;
        अचिह्नित दीर्घ अङ्कः_वस्तूनि_return;
        अचिह्नित दीर्घ अष्टकानि_after_return;
        अचिह्नित वर्ण *tooltype_name_info = रिक्त;

        // Try Wacom-specific method
        यदि (Success == X11_XIGetProperty(दत्त->display, deviceid,
                                         दत्त->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &अङ्कः_वस्तूनि_return, &अष्टकानि_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != रिक्त && अङ्कः_वस्तूनि_return > 0) {

            bool परिणाम = false;
            वर्ण *tooltype_name = रिक्त;

            यदि (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                यदि (atom != None) {
                    tooltype_name = X11_XGetAtomName(दत्त->display, atom);
                }
            } अन्यथा यदि (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (वर्ण *)tooltype_name_info;
            }

            यदि (tooltype_name) {
                यदि (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_चिह्नकम्) == 0) {
                    परिणाम = true;
                }
                यदि (tooltype_name != (वर्ण *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                प्रत्यागम परिणाम;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    प्रत्यागम (SDL_strcasestr(devicename, PEN_ERASER_NAME_चिह्नकम्)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
स्थिर size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, Atom property, Sint32 *dest, size_t max_शब्दाः)
{
    ध्रुव SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Atom type_return;
    पूर्णाङ्क format_return;
    अचिह्नित दीर्घ अङ्कः_वस्तूनि_return;
    अचिह्नित दीर्घ अष्टकानि_after_return;
    अचिह्नित वर्ण *output;

    यदि (property == None) {
        प्रत्यागम 0;
    }

    यदि (Success != X11_XIGetProperty(दत्त->display, deviceid,
                                     property,
                                     0, max_शब्दाः, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &अङ्कः_वस्तूनि_return, &अष्टकानि_after_return,
                                     &output) ||
        अङ्कः_वस्तूनि_return == 0 || output == रिक्त) {
        प्रत्यागम 0;
    }

    यदि (type_return == XA_INTEGER) {
        पूर्णाङ्क k;
        ध्रुव पूर्णाङ्क गन्तव्यम्_copy = SDL_min(max_शब्दाः, अङ्कः_वस्तूनि_return);

        यदि (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            प्रति (k = 0; k < गन्तव्यम्_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा यदि (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            प्रति (k = 0; k < गन्तव्यम्_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा {
            SDL_memcpy(dest, output, परिमाण(Sint32) * गन्तव्यम्_copy);
        }
        X11_XFree(output);
        प्रत्यागम गन्तव्यम्_copy;
    }

    प्रत्यागम 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
स्थिर bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Sint32 serial_id_buf[3];
    पूर्णाङ्क परिणाम;

    यदि ((परिणाम = X11_XInput2PenGetIntProperty(_this, deviceid, दत्त->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        प्रत्यागम true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    प्रत्यागम false;
}

// Check if a Wacom device is in proximity of the tablet
स्थिर bool X11_XInput2_Pen_Is_अन्तर्_Proximity(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, bool *अन्तर्_proximity)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Sint32 serial_id_buf[5];
    यदि (X11_XInput2PenGetIntProperty(_this, deviceid, दत्त->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *अन्तर्_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
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
    FindPenByDeviceIDData *दत्त = (FindPenByDeviceIDData *) userdata;
    यदि (x11_handle->x11_deviceid != दत्त->x11_deviceid) {
        प्रत्यागम false;
    }
    दत्त->handle = handle;
    प्रत्यागम true;
}

X11_PenHandle *X11_FindPenByDeviceID(पूर्णाङ्क deviceid)
{
    FindPenByDeviceIDData दत्त;
    दत्त.x11_deviceid = deviceid;
    दत्त.handle = रिक्त;
    SDL_FindPenByCallback(FindPenByDeviceID, &दत्त);
    प्रत्यागम (X11_PenHandle *) दत्त.handle;
}

स्थिर X11_PenHandle *X11_Maybe_सङ्कलय_Pen(SDL_VideoDevice *_this, ध्रुव XIDeviceInfo *dev)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
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

    पूर्णाङ्क योग_buttons = 0;
    प्रति (पूर्णाङ्क i = 0; i < dev->अङ्कः_classes; i++) {
        ध्रुव XIAnyClassInfo *classinfo = dev->classes[i];
        यदि (classinfo->type == XIButtonClass) {
            ध्रुव XIButtonClassInfo *button_classinfo = (ध्रुव XIButtonClassInfo *)classinfo;
            योग_buttons += button_classinfo->अङ्कः_buttons;
        } अन्यथा यदि (classinfo->type == XIValuatorClass) {
            ध्रुव XIValuatorClassInfo *val_classinfo = (ध्रुव XIValuatorClassInfo *)classinfo;
            ध्रुव Sint8 valuator_nr = val_classinfo->सङ्ख्या_2;
            ध्रुव Atom vname = val_classinfo->label;
            ध्रुव भिन्न min = (भिन्न)val_classinfo->min;
            ध्रुव भिन्न max = (भिन्न)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_गणनम्;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            यदि (vname == दत्त->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } अन्यथा यदि (vname == दत्त->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } अन्यथा यदि (vname == दत्त->atoms.pen_atom_abs_tilt_y) {
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
    peninfo.अङ्कः_buttons = योग_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    यदि (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool अन्तर्_proximity = false;
    यदि (!X11_XInput2_Pen_Is_अन्तर्_Proximity(_this, dev->deviceid, &अन्तर्_proximity)) {
        अन्तर्_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_सङ्कलय_Pen_Device(0, dev->name, रिक्त, &peninfo, handle, अन्तर्_proximity);
    यदि (!handle->pen) {
        SDL_free(handle);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम handle;
}

X11_PenHandle *X11_Maybe_सङ्कलय_Pen_By_Device_ID(SDL_VideoDevice *_this, पूर्णाङ्क deviceid)
{
    यदि (X11_Xinput2IsInitialized()) {
        SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
        पूर्णाङ्क अङ्कः_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(दत्त->display, deviceid, &अङ्कः_device_info);
        यदि (device_info) {
            SDL_assert(अङ्कः_device_info == 1);
            X11_PenHandle *handle = X11_Maybe_सङ्कलय_Pen(_this, device_info);
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

शून्य X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, पूर्णाङ्क deviceid)
{
    bool अन्तर्_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    यदि (pen && X11_XInput2_Pen_Is_अन्तर्_Proximity(_this, deviceid, &अन्तर्_proximity)) {
        SDL_SendPenProximity(0, pen->pen, गवाक्षः, अन्तर्_proximity, अन्तर्_proximity);
    }
}

शून्य X11_InitPen(SDL_VideoDevice *_this)
{
    यदि (!X11_Xinput2IsInitialized()) {
        प्रत्यागम;  // we need XIQueryDevice() for this.
    }

    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    #परिभाषय LOOKUP_PEN_ATOM(X) X11_XInternAtom(दत्त->display, X, False)
    दत्त->atoms.pen_atom_device_गुणनफलम्_id = LOOKUP_PEN_ATOM("Device Product ID");
    दत्त->atoms.pen_atom_wacom_serial_ids = LOOKUP_PEN_ATOM("Wacom Serial IDs");
    दत्त->atoms.pen_atom_wacom_tool_type = LOOKUP_PEN_ATOM("Wacom Tool Type");
    दत्त->atoms.pen_atom_abs_pressure = LOOKUP_PEN_ATOM("Abs Pressure");
    दत्त->atoms.pen_atom_abs_tilt_x = LOOKUP_PEN_ATOM("Abs Tilt X");
    दत्त->atoms.pen_atom_abs_tilt_y = LOOKUP_PEN_ATOM("Abs Tilt Y");
    #अपरिभाषय LOOKUP_PEN_ATOM

    // Do an initial check on devices. After this, we'll add/remove individual pens when XI_HierarchyChanged events alert us.
    पूर्णाङ्क अङ्कः_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(दत्त->display, XIAllDevices, &अङ्कः_device_info);
    यदि (device_info) {
        प्रति (पूर्णाङ्क i = 0; i < अङ्कः_device_info; i++) {
            X11_Maybe_सङ्कलय_Pen(_this, &device_info[i]);
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
    प्रति (पूर्णाङ्क axis = 0; axis < SDL_PEN_AXIS_गणनम्; ++axis) {
        ध्रुव पूर्णाङ्क valuator = pen->valuator_for_axis[axis];
        यदि (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            अनुवर्त;
        }

        भिन्न मानम् = coords[axis];
        ध्रुव भिन्न min = pen->axis_min[axis];
        ध्रुव भिन्न max = pen->axis_max[axis];

        यदि (axis == SDL_PEN_AXIS_SLIDER) {
            मानम् += pen->slider_bias;
        }

        // min ... 0 ... max
        यदि (min < 0.0) {
            // Normalise so that 0 remains 0.0
            यदि (मानम् < 0) {
                मानम् = मानम् / (-min);
            } अन्यथा {
                यदि (max == 0.0f) {
                    मानम् = 0.0f;
                } अन्यथा {
                    मानम् = मानम् / max;
                }
            }
        } अन्यथा {
            // 0 ... min ... max
            // including 0.0 = min
            यदि (max == 0.0f) {
                मानम् = 0.0f;
            } अन्यथा {
                मानम् = (मानम् - min) / max;
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
                मानम् *= 180.0f;
                मानम् += pen->rotation_bias;

                // handle simple over/underflow
                यदि (मानम् >= 180.0f) {
                    मानम् -= 360.0f;
                } अन्यथा यदि (मानम् < -180.0f) {
                    मानम् += 360.0f;
                }
                भङ्ग;

            स्वभाव:
                भङ्ग;
        }

        coords[axis] = मानम्;
    }
}

शून्य X11_PenAxesFromValuators(ध्रुव X11_PenHandle *pen,
                              ध्रुव द्विगुण *निवेशः_मानानि, ध्रुव अचिह्नित वर्ण *आवरणम्, पूर्णाङ्क आवरणम्_len,
                              भिन्न axis_मानानि[SDL_PEN_AXIS_गणनम्])
{
    प्रति (पूर्णाङ्क i = 0; i < SDL_PEN_AXIS_गणनम्; i++) {
        ध्रुव पूर्णाङ्क valuator = pen->valuator_for_axis[i];
        यदि ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= आवरणम्_len * 8) || !(XIMask_Is_समुच्चयः(आवरणम्, valuator))) {
            axis_मानानि[i] = 0.0f;
        } अन्यथा {
            axis_मानानि[i] = (भिन्न)निवेशः_मानानि[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_मानानि);
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

#यदि_अन्तः // SDL_VIDEO_DRIVER_X11_XINPUT2

