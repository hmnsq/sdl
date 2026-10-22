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
स्थिर bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, स्थिरांक XIDeviceInfo *dev)
{
    स्थिरांक SDL_VideoData *data = _this->internal;
    साठी (पूर्णांक i = 0; i < dev->अंक_classes; i++) {
        स्थिरांक XIAnyClassInfo *classinfo = dev->classes[i];
        जर (classinfo->type == XIValuatorClass) {
            स्थिरांक XIValuatorClassInfo *val_classinfo = (स्थिरांक XIValuatorClassInfo *)classinfo;
            जर (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                परत true;
            }
        }
    }

    परत false;
}

// Heuristically determines if device is an eraser
स्थिर bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, पूर्णांक deviceid, अक्षर *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    जर (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        पूर्णांक format_return;
        अचिन्हित दीर्घ अंक_वस्तुसंच_return;
        अचिन्हित दीर्घ bytes_after_return;
        अचिन्हित अक्षर *tooltype_name_info = रिक्त;

        // Try Wacom-specific method
        जर (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &अंक_वस्तुसंच_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != रिक्त && अंक_वस्तुसंच_return > 0) {

            bool result = false;
            अक्षर *tooltype_name = रिक्त;

            जर (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                जर (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } अन्यथा जर (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (अक्षर *)tooltype_name_info;
            }

            जर (tooltype_name) {
                जर (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                जर (tooltype_name != (अक्षर *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                परत result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    परत (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
स्थिर माप_प्रकार X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, पूर्णांक deviceid, Atom property, Sint32 *dest, माप_प्रकार max_शब्द)
{
    स्थिरांक SDL_VideoData *data = _this->internal;
    Atom type_return;
    पूर्णांक format_return;
    अचिन्हित दीर्घ अंक_वस्तुसंच_return;
    अचिन्हित दीर्घ bytes_after_return;
    अचिन्हित अक्षर *output;

    जर (property == None) {
        परत 0;
    }

    जर (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_शब्द, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &अंक_वस्तुसंच_return, &bytes_after_return,
                                     &output) ||
        अंक_वस्तुसंच_return == 0 || output == रिक्त) {
        परत 0;
    }

    जर (type_return == XA_INTEGER) {
        पूर्णांक k;
        स्थिरांक पूर्णांक to_copy = SDL_min(max_शब्द, अंक_वस्तुसंच_return);

        जर (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            साठी (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा जर (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            साठी (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा {
            SDL_memcpy(dest, output, आकार(Sint32) * to_copy);
        }
        X11_XFree(output);
        परत to_copy;
    }

    परत 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
स्थिर bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, पूर्णांक deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    पूर्णांक result;

    जर ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        परत true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    परत false;
}

// Check if a Wacom device is in proximity of the tablet
स्थिर bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, पूर्णांक deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    जर (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        परत true;
    }
    परत false;
}


प्रकारव्याख्या संरचना FindPenByDeviceIDData
{
    पूर्णांक x11_deviceid;
    शून्य *handle;
} FindPenByDeviceIDData;

स्थिर bool FindPenByDeviceID(शून्य *handle, शून्य *userdata)
{
    स्थिरांक X11_PenHandle *x11_handle = (स्थिरांक X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    जर (x11_handle->x11_deviceid != data->x11_deviceid) {
        परत false;
    }
    data->handle = handle;
    परत true;
}

X11_PenHandle *X11_FindPenByDeviceID(पूर्णांक deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = रिक्त;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    परत (X11_PenHandle *) data.handle;
}

स्थिर X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, स्थिरांक XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = रिक्त;

    जर ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        परत रिक्त;  // Only track physical devices that are enabled and look like pens
    } अन्यथा जर ((handle = X11_FindPenByDeviceID(dev->deviceid)) != रिक्त) {
        परत handle;  // already have this pen, skip it.
    } अन्यथा जर ((handle = SDL_calloc(1, आकार(*handle))) == रिक्त) {
        परत रिक्त;  // oh well.
    }

    साठी (पूर्णांक i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    पूर्णांक total_buttons = 0;
    साठी (पूर्णांक i = 0; i < dev->अंक_classes; i++) {
        स्थिरांक XIAnyClassInfo *classinfo = dev->classes[i];
        जर (classinfo->type == XIButtonClass) {
            स्थिरांक XIButtonClassInfo *button_classinfo = (स्थिरांक XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->अंक_buttons;
        } अन्यथा जर (classinfo->type == XIValuatorClass) {
            स्थिरांक XIValuatorClassInfo *val_classinfo = (स्थिरांक XIValuatorClassInfo *)classinfo;
            स्थिरांक Sint8 valuator_nr = val_classinfo->संख्या_2;
            स्थिरांक Atom vname = val_classinfo->label;
            स्थिरांक दशांश min = (दशांश)val_classinfo->min;
            स्थिरांक दशांश max = (दशांश)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_मोजणी;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            जर (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } अन्यथा जर (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } अन्यथा जर (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } अन्यथा {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            जर (use_this_axis) {
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

    स्थिरांक bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
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
    जर (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    जर (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, रिक्त, &peninfo, handle, in_proximity);
    जर (!handle->pen) {
        SDL_free(handle);
        परत रिक्त;
    }

    परत handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, पूर्णांक deviceid)
{
    जर (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        पूर्णांक अंक_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &अंक_device_info);
        जर (device_info) {
            SDL_assert(अंक_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            परत handle;
        }
    }
    परत रिक्त;
}

शून्य X11_RemovePenByDeviceID(पूर्णांक deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    जर (handle) {
        SDL_RemovePenDevice(0, रिक्त, handle->pen);
        SDL_free(handle);
    }
}

शून्य X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    जर (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

शून्य X11_InitPen(SDL_VideoDevice *_this)
{
    जर (!X11_Xinput2IsInitialized()) {
        परत;  // we need XIQueryDevice() for this.
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
    पूर्णांक अंक_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &अंक_device_info);
    जर (device_info) {
        साठी (पूर्णांक i = 0; i < अंक_device_info; i++) {
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

स्थिर शून्य X11_XInput2NormalizePenAxes(स्थिरांक X11_PenHandle *pen, दशांश *coords)
{
    // Normalise axes
    साठी (पूर्णांक axis = 0; axis < SDL_PEN_AXIS_मोजणी; ++axis) {
        स्थिरांक पूर्णांक valuator = pen->valuator_for_axis[axis];
        जर (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            सुरूठेवा;
        }

        दशांश मूल्य = coords[axis];
        स्थिरांक दशांश min = pen->axis_min[axis];
        स्थिरांक दशांश max = pen->axis_max[axis];

        जर (axis == SDL_PEN_AXIS_SLIDER) {
            मूल्य += pen->slider_bias;
        }

        // min ... 0 ... max
        जर (min < 0.0) {
            // Normalise so that 0 remains 0.0
            जर (मूल्य < 0) {
                मूल्य = मूल्य / (-min);
            } अन्यथा {
                जर (max == 0.0f) {
                    मूल्य = 0.0f;
                } अन्यथा {
                    मूल्य = मूल्य / max;
                }
            }
        } अन्यथा {
            // 0 ... min ... max
            // including 0.0 = min
            जर (max == 0.0f) {
                मूल्य = 0.0f;
            } अन्यथा {
                मूल्य = (मूल्य - min) / max;
            }
        }

        निवड (axis) {
            स्थिती SDL_PEN_AXIS_XTILT:
            स्थिती SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                थांबा;

            स्थिती SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                मूल्य *= 180.0f;
                मूल्य += pen->rotation_bias;

                // handle simple over/underflow
                जर (मूल्य >= 180.0f) {
                    मूल्य -= 360.0f;
                } अन्यथा जर (मूल्य < -180.0f) {
                    मूल्य += 360.0f;
                }
                थांबा;

            पूर्वनिर्धारित:
                थांबा;
        }

        coords[axis] = मूल्य;
    }
}

शून्य X11_PenAxesFromValuators(स्थिरांक X11_PenHandle *pen,
                              स्थिरांक द्विगुण *आदान_मूल्ये, स्थिरांक अचिन्हित अक्षर *mask, पूर्णांक mask_len,
                              दशांश axis_मूल्ये[SDL_PEN_AXIS_मोजणी])
{
    साठी (पूर्णांक i = 0; i < SDL_PEN_AXIS_मोजणी; i++) {
        स्थिरांक पूर्णांक valuator = pen->valuator_for_axis[i];
        जर ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_मूल्ये[i] = 0.0f;
        } अन्यथा {
            axis_मूल्ये[i] = (दशांश)आदान_मूल्ये[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_मूल्ये);
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

