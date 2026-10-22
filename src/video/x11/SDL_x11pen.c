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
#समावेश "../../SDL_internal.h"

#समावेश "../../events/SDL_pen_c.h"
#समावेश "../SDL_sysvideo.h"
#समावेश "SDL_x11pen.h"
#समावेश "SDL_x11video.h"
#समावेश "SDL_x11xinput2.h"

#अगर_घोषित SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
अटल bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, स्थिर XIDeviceInfo *dev)
{
    स्थिर SDL_Video_तथ्य *तथ्य = _this->internal;
    क्रम (पूर्णांक i = 0; i < dev->अंक_classes; i++) {
        स्थिर XIAnyClassInfo *classinfo = dev->classes[i];
        अगर (classinfo->type == XIValuatorClass) {
            स्थिर XIValuatorClassInfo *val_classinfo = (स्थिर XIValuatorClassInfo *)classinfo;
            अगर (val_classinfo->label == तथ्य->atoms.pen_atom_abs_pressure) {
                वापस true;
            }
        }
    }

    वापस false;
}

// Heuristically determines if device is an eraser
अटल bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, पूर्णांक deviceid, अक्षर *devicename)
{
    #घोषणा PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_Video_तथ्य *तथ्य = _this->internal;

    अगर (तथ्य->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        पूर्णांक format_return;
        अचिन्हित दीर्घ अंक_वस्तुएँ_return;
        अचिन्हित दीर्घ bytes_after_return;
        अचिन्हित अक्षर *tooltype_name_info = शून्य;

        // Try Wacom-specific method
        अगर (Success == X11_XIGetProperty(तथ्य->display, deviceid,
                                         तथ्य->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &अंक_वस्तुएँ_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != शून्य && अंक_वस्तुएँ_return > 0) {

            bool परिणाम = false;
            अक्षर *tooltype_name = शून्य;

            अगर (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                अगर (atom != None) {
                    tooltype_name = X11_XGetAtomName(तथ्य->display, atom);
                }
            } अन्यथा अगर (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (अक्षर *)tooltype_name_info;
            }

            अगर (tooltype_name) {
                अगर (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    परिणाम = true;
                }
                अगर (tooltype_name != (अक्षर *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                वापस परिणाम;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    वापस (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
अटल माप_प्रकार X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, पूर्णांक deviceid, Atom property, Sint32 *dest, माप_प्रकार max_शब्दगण)
{
    स्थिर SDL_Video_तथ्य *तथ्य = _this->internal;
    Atom type_return;
    पूर्णांक format_return;
    अचिन्हित दीर्घ अंक_वस्तुएँ_return;
    अचिन्हित दीर्घ bytes_after_return;
    अचिन्हित अक्षर *output;

    अगर (property == None) {
        वापस 0;
    }

    अगर (Success != X11_XIGetProperty(तथ्य->display, deviceid,
                                     property,
                                     0, max_शब्दगण, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &अंक_वस्तुएँ_return, &bytes_after_return,
                                     &output) ||
        अंक_वस्तुएँ_return == 0 || output == शून्य) {
        वापस 0;
    }

    अगर (type_return == XA_INTEGER) {
        पूर्णांक k;
        स्थिर पूर्णांक to_copy = SDL_min(max_शब्दगण, अंक_वस्तुएँ_return);

        अगर (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            क्रम (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा अगर (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            क्रम (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } अन्यथा {
            SDL_memcpy(dest, output, माप(Sint32) * to_copy);
        }
        X11_XFree(output);
        वापस to_copy;
    }

    वापस 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
अटल bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, पूर्णांक deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    Sint32 serial_id_buf[3];
    पूर्णांक परिणाम;

    अगर ((परिणाम = X11_XInput2PenGetIntProperty(_this, deviceid, तथ्य->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        वापस true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    वापस false;
}

// Check if a Wacom device is in proximity of the tablet
अटल bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, पूर्णांक deviceid, bool *in_proximity)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    Sint32 serial_id_buf[5];
    अगर (X11_XInput2PenGetIntProperty(_this, deviceid, तथ्य->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        वापस true;
    }
    वापस false;
}


प्रकार काष्ठा FindPenByDeviceIDData
{
    पूर्णांक x11_deviceid;
    व्योम *handle;
} FindPenByDeviceIDData;

अटल bool FindPenByDeviceID(व्योम *handle, व्योम *userdata)
{
    स्थिर X11_PenHandle *x11_handle = (स्थिर X11_PenHandle *) handle;
    FindPenByDeviceIDData *तथ्य = (FindPenByDeviceIDData *) userdata;
    अगर (x11_handle->x11_deviceid != तथ्य->x11_deviceid) {
        वापस false;
    }
    तथ्य->handle = handle;
    वापस true;
}

X11_PenHandle *X11_FindPenByDeviceID(पूर्णांक deviceid)
{
    FindPenByDeviceIDData तथ्य;
    तथ्य.x11_deviceid = deviceid;
    तथ्य.handle = शून्य;
    SDL_FindPenByCallback(FindPenByDeviceID, &तथ्य);
    वापस (X11_PenHandle *) तथ्य.handle;
}

अटल X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, स्थिर XIDeviceInfo *dev)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = शून्य;

    अगर ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        वापस शून्य;  // Only track physical devices that are enabled and look like pens
    } अन्यथा अगर ((handle = X11_FindPenByDeviceID(dev->deviceid)) != शून्य) {
        वापस handle;  // already have this pen, skip it.
    } अन्यथा अगर ((handle = SDL_calloc(1, माप(*handle))) == शून्य) {
        वापस शून्य;  // oh well.
    }

    क्रम (पूर्णांक i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    पूर्णांक योग_buttons = 0;
    क्रम (पूर्णांक i = 0; i < dev->अंक_classes; i++) {
        स्थिर XIAnyClassInfo *classinfo = dev->classes[i];
        अगर (classinfo->type == XIButtonClass) {
            स्थिर XIButtonClassInfo *button_classinfo = (स्थिर XIButtonClassInfo *)classinfo;
            योग_buttons += button_classinfo->अंक_buttons;
        } अन्यथा अगर (classinfo->type == XIValuatorClass) {
            स्थिर XIValuatorClassInfo *val_classinfo = (स्थिर XIValuatorClassInfo *)classinfo;
            स्थिर Sint8 valuator_nr = val_classinfo->संख्या_2;
            स्थिर Atom vname = val_classinfo->label;
            स्थिर भग्न min = (भग्न)val_classinfo->min;
            स्थिर भग्न max = (भग्न)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_गिनती;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            अगर (vname == तथ्य->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } अन्यथा अगर (vname == तथ्य->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } अन्यथा अगर (vname == तथ्य->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } अन्यथा {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            अगर (use_this_axis) {
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

    स्थिर bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.अंक_buttons = योग_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    अगर (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    अगर (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, शून्य, &peninfo, handle, in_proximity);
    अगर (!handle->pen) {
        SDL_free(handle);
        वापस शून्य;
    }

    वापस handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, पूर्णांक deviceid)
{
    अगर (X11_Xinput2IsInitialized()) {
        SDL_Video_तथ्य *तथ्य = _this->internal;
        पूर्णांक अंक_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(तथ्य->display, deviceid, &अंक_device_info);
        अगर (device_info) {
            SDL_assert(अंक_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            वापस handle;
        }
    }
    वापस शून्य;
}

व्योम X11_RemovePenByDeviceID(पूर्णांक deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    अगर (handle) {
        SDL_RemovePenDevice(0, शून्य, handle->pen);
        SDL_free(handle);
    }
}

व्योम X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, पूर्णांक deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    अगर (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

व्योम X11_InitPen(SDL_VideoDevice *_this)
{
    अगर (!X11_Xinput2IsInitialized()) {
        वापस;  // we need XIQueryDevice() for this.
    }

    SDL_Video_तथ्य *तथ्य = _this->internal;

    #घोषणा LOOKUP_PEN_ATOM(X) X11_XInternAtom(तथ्य->display, X, False)
    तथ्य->atoms.pen_atom_device_product_id = LOOKUP_PEN_ATOM("Device Product ID");
    तथ्य->atoms.pen_atom_wacom_serial_ids = LOOKUP_PEN_ATOM("Wacom Serial IDs");
    तथ्य->atoms.pen_atom_wacom_tool_type = LOOKUP_PEN_ATOM("Wacom Tool Type");
    तथ्य->atoms.pen_atom_abs_pressure = LOOKUP_PEN_ATOM("Abs Pressure");
    तथ्य->atoms.pen_atom_abs_tilt_x = LOOKUP_PEN_ATOM("Abs Tilt X");
    तथ्य->atoms.pen_atom_abs_tilt_y = LOOKUP_PEN_ATOM("Abs Tilt Y");
    #अघोषित LOOKUP_PEN_ATOM

    // Do an initial check on devices. After this, we'll add/remove individual pens when XI_HierarchyChanged events alert us.
    पूर्णांक अंक_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(तथ्य->display, XIAllDevices, &अंक_device_info);
    अगर (device_info) {
        क्रम (पूर्णांक i = 0; i < अंक_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

अटल व्योम X11_FreePenHandle(SDL_PenID instance_id, व्योम *handle, व्योम *userdata)
{
    SDL_free(handle);
}

व्योम X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, शून्य);
}

अटल व्योम X11_XInput2NormalizePenAxes(स्थिर X11_PenHandle *pen, भग्न *coords)
{
    // Normalise axes
    क्रम (पूर्णांक axis = 0; axis < SDL_PEN_AXIS_गिनती; ++axis) {
        स्थिर पूर्णांक valuator = pen->valuator_for_axis[axis];
        अगर (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            जारी;
        }

        भग्न मूल्य = coords[axis];
        स्थिर भग्न min = pen->axis_min[axis];
        स्थिर भग्न max = pen->axis_max[axis];

        अगर (axis == SDL_PEN_AXIS_SLIDER) {
            मूल्य += pen->slider_bias;
        }

        // min ... 0 ... max
        अगर (min < 0.0) {
            // Normalise so that 0 remains 0.0
            अगर (मूल्य < 0) {
                मूल्य = मूल्य / (-min);
            } अन्यथा {
                अगर (max == 0.0f) {
                    मूल्य = 0.0f;
                } अन्यथा {
                    मूल्य = मूल्य / max;
                }
            }
        } अन्यथा {
            // 0 ... min ... max
            // including 0.0 = min
            अगर (max == 0.0f) {
                मूल्य = 0.0f;
            } अन्यथा {
                मूल्य = (मूल्य - min) / max;
            }
        }

        चयन (axis) {
            हाल SDL_PEN_AXIS_XTILT:
            हाल SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                अवरोध;

            हाल SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                मूल्य *= 180.0f;
                मूल्य += pen->rotation_bias;

                // handle simple over/underflow
                अगर (मूल्य >= 180.0f) {
                    मूल्य -= 360.0f;
                } अन्यथा अगर (मूल्य < -180.0f) {
                    मूल्य += 360.0f;
                }
                अवरोध;

            शेष:
                अवरोध;
        }

        coords[axis] = मूल्य;
    }
}

व्योम X11_PenAxesFromValuators(स्थिर X11_PenHandle *pen,
                              स्थिर द्विगुन *निवेश_मूल्यावली, स्थिर अचिन्हित अक्षर *mask, पूर्णांक mask_len,
                              भग्न axis_मूल्यावली[SDL_PEN_AXIS_गिनती])
{
    क्रम (पूर्णांक i = 0; i < SDL_PEN_AXIS_गिनती; i++) {
        स्थिर पूर्णांक valuator = pen->valuator_for_axis[i];
        अगर ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_मूल्यावली[i] = 0.0f;
        } अन्यथा {
            axis_मूल्यावली[i] = (भग्न)निवेश_मूल्यावली[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_मूल्यावली);
}

#अन्यथा

व्योम X11_InitPen(SDL_VideoDevice *_this)
{
    (व्योम) _this;
}

व्योम X11_QuitPen(SDL_VideoDevice *_this)
{
    (व्योम) _this;
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_X11_XINPUT2

