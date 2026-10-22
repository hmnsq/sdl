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
#અન્તર્ભાવ "../../SDL_internal.h"

#અન્તર્ભાવ "../../events/SDL_pen_c.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "SDL_x11pen.h"
#અન્તર્ભાવ "SDL_x11video.h"
#અન્તર્ભાવ "SDL_x11xinput2.h"

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
સ્થિર bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, અચલ XIDeviceInfo *dev)
{
    અચલ SDL_VideoData *data = _this->internal;
    માટે (પૂર્ણાંક i = 0; i < dev->અંક_classes; i++) {
        અચલ XIAnyClassInfo *classinfo = dev->classes[i];
        જો (classinfo->type == XIValuatorClass) {
            અચલ XIValuatorClassInfo *val_classinfo = (અચલ XIValuatorClassInfo *)classinfo;
            જો (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                પાછા true;
            }
        }
    }

    પાછા false;
}

// Heuristically determines if device is an eraser
સ્થિર bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, પૂર્ણાંક deviceid, અક્ષર *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    જો (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        પૂર્ણાંક format_return;
        unsigned long અંક_વસ્તુઓ_return;
        unsigned long bytes_after_return;
        unsigned અક્ષર *tooltype_name_info = ખાલી;

        // Try Wacom-specific method
        જો (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &અંક_વસ્તુઓ_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != ખાલી && અંક_વસ્તુઓ_return > 0) {

            bool result = false;
            અક્ષર *tooltype_name = ખાલી;

            જો (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                જો (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } નહીંતર જો (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (અક્ષર *)tooltype_name_info;
            }

            જો (tooltype_name) {
                જો (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                જો (tooltype_name != (અક્ષર *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                પાછા result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    પાછા (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
સ્થિર size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, પૂર્ણાંક deviceid, Atom property, Sint32 *dest, size_t max_શબ્દો)
{
    અચલ SDL_VideoData *data = _this->internal;
    Atom type_return;
    પૂર્ણાંક format_return;
    unsigned long અંક_વસ્તુઓ_return;
    unsigned long bytes_after_return;
    unsigned અક્ષર *output;

    જો (property == None) {
        પાછા 0;
    }

    જો (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_શબ્દો, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &અંક_વસ્તુઓ_return, &bytes_after_return,
                                     &output) ||
        અંક_વસ્તુઓ_return == 0 || output == ખાલી) {
        પાછા 0;
    }

    જો (type_return == XA_INTEGER) {
        પૂર્ણાંક k;
        અચલ પૂર્ણાંક to_copy = SDL_min(max_શબ્દો, અંક_વસ્તુઓ_return);

        જો (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            માટે (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } નહીંતર જો (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            માટે (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } નહીંતર {
            SDL_memcpy(dest, output, કદ(Sint32) * to_copy);
        }
        X11_XFree(output);
        પાછા to_copy;
    }

    પાછા 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
સ્થિર bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, પૂર્ણાંક deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    પૂર્ણાંક result;

    જો ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        પાછા true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    પાછા false;
}

// Check if a Wacom device is in proximity of the tablet
સ્થિર bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, પૂર્ણાંક deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    જો (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        પાછા true;
    }
    પાછા false;
}


પ્રકારવ્યાખ્યા સંરચના FindPenByDeviceIDData
{
    પૂર્ણાંક x11_deviceid;
    શૂન્ય *handle;
} FindPenByDeviceIDData;

સ્થિર bool FindPenByDeviceID(શૂન્ય *handle, શૂન્ય *userdata)
{
    અચલ X11_PenHandle *x11_handle = (અચલ X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    જો (x11_handle->x11_deviceid != data->x11_deviceid) {
        પાછા false;
    }
    data->handle = handle;
    પાછા true;
}

X11_PenHandle *X11_FindPenByDeviceID(પૂર્ણાંક deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = ખાલી;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    પાછા (X11_PenHandle *) data.handle;
}

સ્થિર X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, અચલ XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = ખાલી;

    જો ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        પાછા ખાલી;  // Only track physical devices that are enabled and look like pens
    } નહીંતર જો ((handle = X11_FindPenByDeviceID(dev->deviceid)) != ખાલી) {
        પાછા handle;  // already have this pen, skip it.
    } નહીંતર જો ((handle = SDL_calloc(1, કદ(*handle))) == ખાલી) {
        પાછા ખાલી;  // oh well.
    }

    માટે (પૂર્ણાંક i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    પૂર્ણાંક total_buttons = 0;
    માટે (પૂર્ણાંક i = 0; i < dev->અંક_classes; i++) {
        અચલ XIAnyClassInfo *classinfo = dev->classes[i];
        જો (classinfo->type == XIButtonClass) {
            અચલ XIButtonClassInfo *button_classinfo = (અચલ XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->અંક_buttons;
        } નહીંતર જો (classinfo->type == XIValuatorClass) {
            અચલ XIValuatorClassInfo *val_classinfo = (અચલ XIValuatorClassInfo *)classinfo;
            અચલ Sint8 valuator_nr = val_classinfo->સંખ્યા_2;
            અચલ Atom vname = val_classinfo->label;
            અચલ દશાંશ min = (દશાંશ)val_classinfo->min;
            અચલ દશાંશ max = (દશાંશ)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_ગણતરી;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            જો (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } નહીંતર જો (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } નહીંતર જો (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } નહીંતર {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            જો (use_this_axis) {
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

    અચલ bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.અંક_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    જો (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    જો (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, ખાલી, &peninfo, handle, in_proximity);
    જો (!handle->pen) {
        SDL_free(handle);
        પાછા ખાલી;
    }

    પાછા handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, પૂર્ણાંક deviceid)
{
    જો (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        પૂર્ણાંક અંક_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &અંક_device_info);
        જો (device_info) {
            SDL_assert(અંક_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            પાછા handle;
        }
    }
    પાછા ખાલી;
}

શૂન્ય X11_RemovePenByDeviceID(પૂર્ણાંક deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    જો (handle) {
        SDL_RemovePenDevice(0, ખાલી, handle->pen);
        SDL_free(handle);
    }
}

શૂન્ય X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, પૂર્ણાંક deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    જો (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

શૂન્ય X11_InitPen(SDL_VideoDevice *_this)
{
    જો (!X11_Xinput2IsInitialized()) {
        પાછા;  // we need XIQueryDevice() for this.
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
    પૂર્ણાંક અંક_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &અંક_device_info);
    જો (device_info) {
        માટે (પૂર્ણાંક i = 0; i < અંક_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

સ્થિર શૂન્ય X11_FreePenHandle(SDL_PenID instance_id, શૂન્ય *handle, શૂન્ય *userdata)
{
    SDL_free(handle);
}

શૂન્ય X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, ખાલી);
}

સ્થિર શૂન્ય X11_XInput2NormalizePenAxes(અચલ X11_PenHandle *pen, દશાંશ *coords)
{
    // Normalise axes
    માટે (પૂર્ણાંક axis = 0; axis < SDL_PEN_AXIS_ગણતરી; ++axis) {
        અચલ પૂર્ણાંક valuator = pen->valuator_for_axis[axis];
        જો (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            ચાલુ;
        }

        દશાંશ કિંમત = coords[axis];
        અચલ દશાંશ min = pen->axis_min[axis];
        અચલ દશાંશ max = pen->axis_max[axis];

        જો (axis == SDL_PEN_AXIS_SLIDER) {
            કિંમત += pen->slider_bias;
        }

        // min ... 0 ... max
        જો (min < 0.0) {
            // Normalise so that 0 remains 0.0
            જો (કિંમત < 0) {
                કિંમત = કિંમત / (-min);
            } નહીંતર {
                જો (max == 0.0f) {
                    કિંમત = 0.0f;
                } નહીંતર {
                    કિંમત = કિંમત / max;
                }
            }
        } નહીંતર {
            // 0 ... min ... max
            // including 0.0 = min
            જો (max == 0.0f) {
                કિંમત = 0.0f;
            } નહીંતર {
                કિંમત = (કિંમત - min) / max;
            }
        }

        પસંદગી (axis) {
            સ્થિતિ SDL_PEN_AXIS_XTILT:
            સ્થિતિ SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                તોડો;

            સ્થિતિ SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                કિંમત *= 180.0f;
                કિંમત += pen->rotation_bias;

                // handle simple over/underflow
                જો (કિંમત >= 180.0f) {
                    કિંમત -= 360.0f;
                } નહીંતર જો (કિંમત < -180.0f) {
                    કિંમત += 360.0f;
                }
                તોડો;

            મૂળભૂત:
                તોડો;
        }

        coords[axis] = કિંમત;
    }
}

શૂન્ય X11_PenAxesFromValuators(અચલ X11_PenHandle *pen,
                              અચલ દ્વિગુણ *આગત_કિંમતો, અચલ unsigned અક્ષર *mask, પૂર્ણાંક mask_len,
                              દશાંશ axis_કિંમતો[SDL_PEN_AXIS_ગણતરી])
{
    માટે (પૂર્ણાંક i = 0; i < SDL_PEN_AXIS_ગણતરી; i++) {
        અચલ પૂર્ણાંક valuator = pen->valuator_for_axis[i];
        જો ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_કિંમતો[i] = 0.0f;
        } નહીંતર {
            axis_કિંમતો[i] = (દશાંશ)આગત_કિંમતો[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_કિંમતો);
}

#નહીંતર

શૂન્ય X11_InitPen(SDL_VideoDevice *_this)
{
    (શૂન્ય) _this;
}

શૂન્ય X11_QuitPen(SDL_VideoDevice *_this)
{
    (શૂન્ય) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

