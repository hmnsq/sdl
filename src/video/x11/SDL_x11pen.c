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
स्थिर bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, अचर XIDeviceInfo *dev)
{
    अचर SDL_VideoData *data = _this->internal;
    लागि (पूर्णाङ्क i = 0; i < dev->अङ्क_classes; i++) {
        अचर XIAnyClassInfo *classinfo = dev->classes[i];
        यदि (classinfo->type == XIValuatorClass) {
            अचर XIValuatorClassInfo *val_classinfo = (अचर XIValuatorClassInfo *)classinfo;
            यदि (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                फर्काऊ true;
            }
        }
    }

    फर्काऊ false;
}

// Heuristically determines if device is an eraser
स्थिर bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, वर्ण *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    यदि (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        पूर्णाङ्क format_return;
        अचिन्हित दीर्घ अङ्क_वस्तुहरू_return;
        अचिन्हित दीर्घ bytes_after_return;
        अचिन्हित वर्ण *tooltype_name_info = रिक्त;

        // Try Wacom-specific method
        यदि (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &अङ्क_वस्तुहरू_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != रिक्त && अङ्क_वस्तुहरू_return > 0) {

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

                फर्काऊ result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    फर्काऊ (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
स्थिर माप_प्रकार X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, Atom property, Sint32 *dest, माप_प्रकार max_शब्दहरू)
{
    अचर SDL_VideoData *data = _this->internal;
    Atom type_return;
    पूर्णाङ्क format_return;
    अचिन्हित दीर्घ अङ्क_वस्तुहरू_return;
    अचिन्हित दीर्घ bytes_after_return;
    अचिन्हित वर्ण *output;

    यदि (property == None) {
        फर्काऊ 0;
    }

    यदि (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_शब्दहरू, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &अङ्क_वस्तुहरू_return, &bytes_after_return,
                                     &output) ||
        अङ्क_वस्तुहरू_return == 0 || output == रिक्त) {
        फर्काऊ 0;
    }

    यदि (type_return == XA_INTEGER) {
        पूर्णाङ्क k;
        अचर पूर्णाङ्क to_copy = SDL_min(max_शब्दहरू, अङ्क_वस्तुहरू_return);

        यदि (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            लागि (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा यदि (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            लागि (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा {
            SDL_memcpy(dest, output, परिमाण(Sint32) * to_copy);
        }
        X11_XFree(output);
        फर्काऊ to_copy;
    }

    फर्काऊ 0; // type mismatch
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
        फर्काऊ true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    फर्काऊ false;
}

// Check if a Wacom device is in proximity of the tablet
स्थिर bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, पूर्णाङ्क deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    यदि (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        फर्काऊ true;
    }
    फर्काऊ false;
}


प्रकारनिर्देश संरचना FindPenByDeviceIDData
{
    पूर्णाङ्क x11_deviceid;
    शून्य *handle;
} FindPenByDeviceIDData;

स्थिर bool FindPenByDeviceID(शून्य *handle, शून्य *userdata)
{
    अचर X11_PenHandle *x11_handle = (अचर X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    यदि (x11_handle->x11_deviceid != data->x11_deviceid) {
        फर्काऊ false;
    }
    data->handle = handle;
    फर्काऊ true;
}

X11_PenHandle *X11_FindPenByDeviceID(पूर्णाङ्क deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = रिक्त;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    फर्काऊ (X11_PenHandle *) data.handle;
}

स्थिर X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, अचर XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = रिक्त;

    यदि ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        फर्काऊ रिक्त;  // Only track physical devices that are enabled and look like pens
    } अन्यथा यदि ((handle = X11_FindPenByDeviceID(dev->deviceid)) != रिक्त) {
        फर्काऊ handle;  // already have this pen, skip it.
    } अन्यथा यदि ((handle = SDL_calloc(1, परिमाण(*handle))) == रिक्त) {
        फर्काऊ रिक्त;  // oh well.
    }

    लागि (पूर्णाङ्क i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    पूर्णाङ्क total_buttons = 0;
    लागि (पूर्णाङ्क i = 0; i < dev->अङ्क_classes; i++) {
        अचर XIAnyClassInfo *classinfo = dev->classes[i];
        यदि (classinfo->type == XIButtonClass) {
            अचर XIButtonClassInfo *button_classinfo = (अचर XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->अङ्क_buttons;
        } अन्यथा यदि (classinfo->type == XIValuatorClass) {
            अचर XIValuatorClassInfo *val_classinfo = (अचर XIValuatorClassInfo *)classinfo;
            अचर Sint8 valuator_nr = val_classinfo->सङ्ख्या_2;
            अचर Atom vname = val_classinfo->label;
            अचर भिन्न min = (भिन्न)val_classinfo->min;
            अचर भिन्न max = (भिन्न)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_गन्ती;

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

    अचर bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.अङ्क_buttons = total_buttons;
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
        फर्काऊ रिक्त;
    }

    फर्काऊ handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, पूर्णाङ्क deviceid)
{
    यदि (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        पूर्णाङ्क अङ्क_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &अङ्क_device_info);
        यदि (device_info) {
            SDL_assert(अङ्क_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            फर्काऊ handle;
        }
    }
    फर्काऊ रिक्त;
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
        फर्काऊ;  // we need XIQueryDevice() for this.
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
    पूर्णाङ्क अङ्क_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &अङ्क_device_info);
    यदि (device_info) {
        लागि (पूर्णाङ्क i = 0; i < अङ्क_device_info; i++) {
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

स्थिर शून्य X11_XInput2NormalizePenAxes(अचर X11_PenHandle *pen, भिन्न *coords)
{
    // Normalise axes
    लागि (पूर्णाङ्क axis = 0; axis < SDL_PEN_AXIS_गन्ती; ++axis) {
        अचर पूर्णाङ्क valuator = pen->valuator_for_axis[axis];
        यदि (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            जारी;
        }

        भिन्न मान = coords[axis];
        अचर भिन्न min = pen->axis_min[axis];
        अचर भिन्न max = pen->axis_max[axis];

        यदि (axis == SDL_PEN_AXIS_SLIDER) {
            मान += pen->slider_bias;
        }

        // min ... 0 ... max
        यदि (min < 0.0) {
            // Normalise so that 0 remains 0.0
            यदि (मान < 0) {
                मान = मान / (-min);
            } अन्यथा {
                यदि (max == 0.0f) {
                    मान = 0.0f;
                } अन्यथा {
                    मान = मान / max;
                }
            }
        } अन्यथा {
            // 0 ... min ... max
            // including 0.0 = min
            यदि (max == 0.0f) {
                मान = 0.0f;
            } अन्यथा {
                मान = (मान - min) / max;
            }
        }

        विकल्प (axis) {
            पक्ष SDL_PEN_AXIS_XTILT:
            पक्ष SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                रोक;

            पक्ष SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                मान *= 180.0f;
                मान += pen->rotation_bias;

                // handle simple over/underflow
                यदि (मान >= 180.0f) {
                    मान -= 360.0f;
                } अन्यथा यदि (मान < -180.0f) {
                    मान += 360.0f;
                }
                रोक;

            स्वभाव:
                रोक;
        }

        coords[axis] = मान;
    }
}

शून्य X11_PenAxesFromValuators(अचर X11_PenHandle *pen,
                              अचर द्विगुण *आगत_मानहरू, अचर अचिन्हित वर्ण *mask, पूर्णाङ्क mask_len,
                              भिन्न axis_मानहरू[SDL_PEN_AXIS_गन्ती])
{
    लागि (पूर्णाङ्क i = 0; i < SDL_PEN_AXIS_गन्ती; i++) {
        अचर पूर्णाङ्क valuator = pen->valuator_for_axis[i];
        यदि ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_मानहरू[i] = 0.0f;
        } अन्यथा {
            axis_मानहरू[i] = (भिन्न)आगत_मानहरू[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_मानहरू);
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

