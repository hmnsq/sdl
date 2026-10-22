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
#ଅନ୍ତର୍ଭାଵ "../../SDL_internal.h"

#ଅନ୍ତର୍ଭାଵ "../../events/SDL_pen_c.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11pen.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11video.h"
#ଅନ୍ତର୍ଭାଵ "SDL_x11xinput2.h"

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
ସ୍ଥିର bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, ଅଚଳ XIDeviceInfo *dev)
{
    ଅଚଳ SDL_VideoData *data = _this->internal;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < dev->ଅଙ୍କ_classes; i++) {
        ଅଚଳ XIAnyClassInfo *classinfo = dev->classes[i];
        ଯଦି (classinfo->type == XIValuatorClass) {
            ଅଚଳ XIValuatorClassInfo *val_classinfo = (ଅଚଳ XIValuatorClassInfo *)classinfo;
            ଯଦି (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                ଫେରନ୍ତୁ true;
            }
        }
    }

    ଫେରନ୍ତୁ false;
}

// Heuristically determines if device is an eraser
ସ୍ଥିର bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid, ଅକ୍ଷର *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    ଯଦି (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା format_return;
        unsigned long ଅଙ୍କ_ବସ୍ତୁଗୁଡ଼ିକ_return;
        unsigned long bytes_after_return;
        unsigned ଅକ୍ଷର *tooltype_name_info = ଖାଲି;

        // Try Wacom-specific method
        ଯଦି (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &ଅଙ୍କ_ବସ୍ତୁଗୁଡ଼ିକ_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != ଖାଲି && ଅଙ୍କ_ବସ୍ତୁଗୁଡ଼ିକ_return > 0) {

            bool result = false;
            ଅକ୍ଷର *tooltype_name = ଖାଲି;

            ଯଦି (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                ଯଦି (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } ଅନ୍ୟଥା ଯଦି (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (ଅକ୍ଷର *)tooltype_name_info;
            }

            ଯଦି (tooltype_name) {
                ଯଦି (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                ଯଦି (tooltype_name != (ଅକ୍ଷର *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                ଫେରନ୍ତୁ result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    ଫେରନ୍ତୁ (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
ସ୍ଥିର size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid, Atom property, Sint32 *dest, size_t max_ଶବ୍ଦଗୁଡ଼ିକ)
{
    ଅଚଳ SDL_VideoData *data = _this->internal;
    Atom type_return;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା format_return;
    unsigned long ଅଙ୍କ_ବସ୍ତୁଗୁଡ଼ିକ_return;
    unsigned long bytes_after_return;
    unsigned ଅକ୍ଷର *output;

    ଯଦି (property == None) {
        ଫେରନ୍ତୁ 0;
    }

    ଯଦି (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_ଶବ୍ଦଗୁଡ଼ିକ, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &ଅଙ୍କ_ବସ୍ତୁଗୁଡ଼ିକ_return, &bytes_after_return,
                                     &output) ||
        ଅଙ୍କ_ବସ୍ତୁଗୁଡ଼ିକ_return == 0 || output == ଖାଲି) {
        ଫେରନ୍ତୁ 0;
    }

    ଯଦି (type_return == XA_INTEGER) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା k;
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା to_copy = SDL_min(max_ଶବ୍ଦଗୁଡ଼ିକ, ଅଙ୍କ_ବସ୍ତୁଗୁଡ଼ିକ_return);

        ଯଦି (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            ପାଇଁ (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ଅନ୍ୟଥା ଯଦି (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            ପାଇଁ (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ଅନ୍ୟଥା {
            SDL_memcpy(dest, output, ଆକାର(Sint32) * to_copy);
        }
        X11_XFree(output);
        ଫେରନ୍ତୁ to_copy;
    }

    ଫେରନ୍ତୁ 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
ସ୍ଥିର bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା result;

    ଯଦି ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        ଫେରନ୍ତୁ true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    ଫେରନ୍ତୁ false;
}

// Check if a Wacom device is in proximity of the tablet
ସ୍ଥିର bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    ଯଦି (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}


ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା FindPenByDeviceIDData
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା x11_deviceid;
    ଶୂନ୍ୟ *handle;
} FindPenByDeviceIDData;

ସ୍ଥିର bool FindPenByDeviceID(ଶୂନ୍ୟ *handle, ଶୂନ୍ୟ *userdata)
{
    ଅଚଳ X11_PenHandle *x11_handle = (ଅଚଳ X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    ଯଦି (x11_handle->x11_deviceid != data->x11_deviceid) {
        ଫେରନ୍ତୁ false;
    }
    data->handle = handle;
    ଫେରନ୍ତୁ true;
}

X11_PenHandle *X11_FindPenByDeviceID(ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = ଖାଲି;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    ଫେରନ୍ତୁ (X11_PenHandle *) data.handle;
}

ସ୍ଥିର X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, ଅଚଳ XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = ଖାଲି;

    ଯଦି ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        ଫେରନ୍ତୁ ଖାଲି;  // Only track physical devices that are enabled and look like pens
    } ଅନ୍ୟଥା ଯଦି ((handle = X11_FindPenByDeviceID(dev->deviceid)) != ଖାଲି) {
        ଫେରନ୍ତୁ handle;  // already have this pen, skip it.
    } ଅନ୍ୟଥା ଯଦି ((handle = SDL_calloc(1, ଆକାର(*handle))) == ଖାଲି) {
        ଫେରନ୍ତୁ ଖାଲି;  // oh well.
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା total_buttons = 0;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < dev->ଅଙ୍କ_classes; i++) {
        ଅଚଳ XIAnyClassInfo *classinfo = dev->classes[i];
        ଯଦି (classinfo->type == XIButtonClass) {
            ଅଚଳ XIButtonClassInfo *button_classinfo = (ଅଚଳ XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->ଅଙ୍କ_buttons;
        } ଅନ୍ୟଥା ଯଦି (classinfo->type == XIValuatorClass) {
            ଅଚଳ XIValuatorClassInfo *val_classinfo = (ଅଚଳ XIValuatorClassInfo *)classinfo;
            ଅଚଳ Sint8 valuator_nr = val_classinfo->ସଂଖ୍ୟା_2;
            ଅଚଳ Atom vname = val_classinfo->label;
            ଅଚଳ ଦଶମିକ min = (ଦଶମିକ)val_classinfo->min;
            ଅଚଳ ଦଶମିକ max = (ଦଶମିକ)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_ଗଣନା;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            ଯଦି (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } ଅନ୍ୟଥା ଯଦି (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } ଅନ୍ୟଥା ଯଦି (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } ଅନ୍ୟଥା {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            ଯଦି (use_this_axis) {
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

    ଅଚଳ bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.ଅଙ୍କ_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    ଯଦି (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    ଯଦି (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, ଖାଲି, &peninfo, handle, in_proximity);
    ଯଦି (!handle->pen) {
        SDL_free(handle);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid)
{
    ଯଦି (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &ଅଙ୍କ_device_info);
        ଯଦି (device_info) {
            SDL_assert(ଅଙ୍କ_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            ଫେରନ୍ତୁ handle;
        }
    }
    ଫେରନ୍ତୁ ଖାଲି;
}

ଶୂନ୍ୟ X11_RemovePenByDeviceID(ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    ଯଦି (handle) {
        SDL_RemovePenDevice(0, ଖାଲି, handle->pen);
        SDL_free(handle);
    }
}

ଶୂନ୍ୟ X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    ଯଦି (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

ଶୂନ୍ୟ X11_InitPen(SDL_VideoDevice *_this)
{
    ଯଦି (!X11_Xinput2IsInitialized()) {
        ଫେରନ୍ତୁ;  // we need XIQueryDevice() for this.
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
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &ଅଙ୍କ_device_info);
    ଯଦି (device_info) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଅଙ୍କ_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ X11_FreePenHandle(SDL_PenID instance_id, ଶୂନ୍ୟ *handle, ଶୂନ୍ୟ *userdata)
{
    SDL_free(handle);
}

ଶୂନ୍ୟ X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, ଖାଲି);
}

ସ୍ଥିର ଶୂନ୍ୟ X11_XInput2NormalizePenAxes(ଅଚଳ X11_PenHandle *pen, ଦଶମିକ *coords)
{
    // Normalise axes
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା axis = 0; axis < SDL_PEN_AXIS_ଗଣନା; ++axis) {
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା valuator = pen->valuator_for_axis[axis];
        ଯଦି (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            ଜାରି;
        }

        ଦଶମିକ ମୂଲ୍ୟ = coords[axis];
        ଅଚଳ ଦଶମିକ min = pen->axis_min[axis];
        ଅଚଳ ଦଶମିକ max = pen->axis_max[axis];

        ଯଦି (axis == SDL_PEN_AXIS_SLIDER) {
            ମୂଲ୍ୟ += pen->slider_bias;
        }

        // min ... 0 ... max
        ଯଦି (min < 0.0) {
            // Normalise so that 0 remains 0.0
            ଯଦି (ମୂଲ୍ୟ < 0) {
                ମୂଲ୍ୟ = ମୂଲ୍ୟ / (-min);
            } ଅନ୍ୟଥା {
                ଯଦି (max == 0.0f) {
                    ମୂଲ୍ୟ = 0.0f;
                } ଅନ୍ୟଥା {
                    ମୂଲ୍ୟ = ମୂଲ୍ୟ / max;
                }
            }
        } ଅନ୍ୟଥା {
            // 0 ... min ... max
            // including 0.0 = min
            ଯଦି (max == 0.0f) {
                ମୂଲ୍ୟ = 0.0f;
            } ଅନ୍ୟଥା {
                ମୂଲ୍ୟ = (ମୂଲ୍ୟ - min) / max;
            }
        }

        ବାଛ (axis) {
            ସ୍ଥିତି SDL_PEN_AXIS_XTILT:
            ସ୍ଥିତି SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                ଭାଙ୍ଗ;

            ସ୍ଥିତି SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                ମୂଲ୍ୟ *= 180.0f;
                ମୂଲ୍ୟ += pen->rotation_bias;

                // handle simple over/underflow
                ଯଦି (ମୂଲ୍ୟ >= 180.0f) {
                    ମୂଲ୍ୟ -= 360.0f;
                } ଅନ୍ୟଥା ଯଦି (ମୂଲ୍ୟ < -180.0f) {
                    ମୂଲ୍ୟ += 360.0f;
                }
                ଭାଙ୍ଗ;

            ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
                ଭାଙ୍ଗ;
        }

        coords[axis] = ମୂଲ୍ୟ;
    }
}

ଶୂନ୍ୟ X11_PenAxesFromValuators(ଅଚଳ X11_PenHandle *pen,
                              ଅଚଳ ଦ୍ୱିଗୁଣ *ନିବେଶ_ମୂଲ୍ୟଗୁଡ଼ିକ, ଅଚଳ unsigned ଅକ୍ଷର *mask, ପୂର୍ଣ୍ଣସଂଖ୍ୟା mask_len,
                              ଦଶମିକ axis_ମୂଲ୍ୟଗୁଡ଼ିକ[SDL_PEN_AXIS_ଗଣନା])
{
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < SDL_PEN_AXIS_ଗଣନା; i++) {
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା valuator = pen->valuator_for_axis[i];
        ଯଦି ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_ମୂଲ୍ୟଗୁଡ଼ିକ[i] = 0.0f;
        } ଅନ୍ୟଥା {
            axis_ମୂଲ୍ୟଗୁଡ଼ିକ[i] = (ଦଶମିକ)ନିବେଶ_ମୂଲ୍ୟଗୁଡ଼ିକ[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_ମୂଲ୍ୟଗୁଡ଼ିକ);
}

#ଅନ୍ୟଥା

ଶୂନ୍ୟ X11_InitPen(SDL_VideoDevice *_this)
{
    (ଶୂନ୍ୟ) _this;
}

ଶୂନ୍ୟ X11_QuitPen(SDL_VideoDevice *_this)
{
    (ଶୂନ୍ୟ) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

