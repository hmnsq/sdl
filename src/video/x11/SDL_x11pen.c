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
#অন্তর্ভাৱ "../../SDL_internal.h"

#অন্তর্ভাৱ "../../events/SDL_pen_c.h"
#অন্তর্ভাৱ "../SDL_sysvideo.h"
#অন্তর্ভাৱ "SDL_x11pen.h"
#অন্তর্ভাৱ "SDL_x11video.h"
#অন্তর্ভাৱ "SDL_x11xinput2.h"

#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
স্থির bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, ধ্রুৱ XIDeviceInfo *dev)
{
    ধ্রুৱ SDL_VideoData *data = _this->internal;
    বাবে (পূর্ণাঙ্ক i = 0; i < dev->অঙ্ক_classes; i++) {
        ধ্রুৱ XIAnyClassInfo *classinfo = dev->classes[i];
        যদি (classinfo->type == XIValuatorClass) {
            ধ্রুৱ XIValuatorClassInfo *val_classinfo = (ধ্রুৱ XIValuatorClassInfo *)classinfo;
            যদি (val_classinfo->label == data->atoms.pen_atom_abs_pressure) {
                ঘূৰাই true;
            }
        }
    }

    ঘূৰাই false;
}

// Heuristically determines if device is an eraser
স্থির bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, পূর্ণাঙ্ক deviceid, ৱর্ণ *devicename)
{
    #define PEN_ERASER_NAME_TAG  "eraser" // String constant to identify erasers
    SDL_VideoData *data = _this->internal;

    যদি (data->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        পূর্ণাঙ্ক format_return;
        unsigned long অঙ্ক_বস্তুসমূহ_return;
        unsigned long bytes_after_return;
        unsigned ৱর্ণ *tooltype_name_info = রিক্ত;

        // Try Wacom-specific method
        যদি (Success == X11_XIGetProperty(data->display, deviceid,
                                         data->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &অঙ্ক_বস্তুসমূহ_return, &bytes_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != রিক্ত && অঙ্ক_বস্তুসমূহ_return > 0) {

            bool result = false;
            ৱর্ণ *tooltype_name = রিক্ত;

            যদি (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                যদি (atom != None) {
                    tooltype_name = X11_XGetAtomName(data->display, atom);
                }
            } অন্যথা যদি (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (ৱর্ণ *)tooltype_name_info;
            }

            যদি (tooltype_name) {
                যদি (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_TAG) == 0) {
                    result = true;
                }
                যদি (tooltype_name != (ৱর্ণ *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                ঘূৰাই result;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    ঘূৰাই (SDL_strcasestr(devicename, PEN_ERASER_NAME_TAG)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
স্থির size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, পূর্ণাঙ্ক deviceid, Atom property, Sint32 *dest, size_t max_শব্দগুলি)
{
    ধ্রুৱ SDL_VideoData *data = _this->internal;
    Atom type_return;
    পূর্ণাঙ্ক format_return;
    unsigned long অঙ্ক_বস্তুসমূহ_return;
    unsigned long bytes_after_return;
    unsigned ৱর্ণ *output;

    যদি (property == None) {
        ঘূৰাই 0;
    }

    যদি (Success != X11_XIGetProperty(data->display, deviceid,
                                     property,
                                     0, max_শব্দগুলি, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &অঙ্ক_বস্তুসমূহ_return, &bytes_after_return,
                                     &output) ||
        অঙ্ক_বস্তুসমূহ_return == 0 || output == রিক্ত) {
        ঘূৰাই 0;
    }

    যদি (type_return == XA_INTEGER) {
        পূর্ণাঙ্ক k;
        ধ্রুৱ পূর্ণাঙ্ক to_copy = SDL_min(max_শব্দগুলি, অঙ্ক_বস্তুসমূহ_return);

        যদি (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            বাবে (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } অন্যথা যদি (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            বাবে (k = 0; k < to_copy; ++k) {
                dest[k] = numdata[k];
            }
        } অন্যথা {
            SDL_memcpy(dest, output, পরিমাণ(Sint32) * to_copy);
        }
        X11_XFree(output);
        ঘূৰাই to_copy;
    }

    ঘূৰাই 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
স্থির bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, পূর্ণাঙ্ক deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[3];
    পূর্ণাঙ্ক result;

    যদি ((result = X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        ঘূৰাই true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    ঘূৰাই false;
}

// Check if a Wacom device is in proximity of the tablet
স্থির bool X11_XInput2PenIsInProximity(SDL_VideoDevice *_this, পূর্ণাঙ্ক deviceid, bool *in_proximity)
{
    SDL_VideoData *data = _this->internal;
    Sint32 serial_id_buf[5];
    যদি (X11_XInput2PenGetIntProperty(_this, deviceid, data->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *in_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        ঘূৰাই true;
    }
    ঘূৰাই false;
}


প্রকারনির্দেশ সংরচনা FindPenByDeviceIDData
{
    পূর্ণাঙ্ক x11_deviceid;
    শূন্য *handle;
} FindPenByDeviceIDData;

স্থির bool FindPenByDeviceID(শূন্য *handle, শূন্য *userdata)
{
    ধ্রুৱ X11_PenHandle *x11_handle = (ধ্রুৱ X11_PenHandle *) handle;
    FindPenByDeviceIDData *data = (FindPenByDeviceIDData *) userdata;
    যদি (x11_handle->x11_deviceid != data->x11_deviceid) {
        ঘূৰাই false;
    }
    data->handle = handle;
    ঘূৰাই true;
}

X11_PenHandle *X11_FindPenByDeviceID(পূর্ণাঙ্ক deviceid)
{
    FindPenByDeviceIDData data;
    data.x11_deviceid = deviceid;
    data.handle = রিক্ত;
    SDL_FindPenByCallback(FindPenByDeviceID, &data);
    ঘূৰাই (X11_PenHandle *) data.handle;
}

স্থির X11_PenHandle *X11_MaybeAddPen(SDL_VideoDevice *_this, ধ্রুৱ XIDeviceInfo *dev)
{
    SDL_VideoData *data = _this->internal;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = রিক্ত;

    যদি ((dev->use != XISlavePointer && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        ঘূৰাই রিক্ত;  // Only track physical devices that are enabled and look like pens
    } অন্যথা যদি ((handle = X11_FindPenByDeviceID(dev->deviceid)) != রিক্ত) {
        ঘূৰাই handle;  // already have this pen, skip it.
    } অন্যথা যদি ((handle = SDL_calloc(1, পরিমাণ(*handle))) == রিক্ত) {
        ঘূৰাই রিক্ত;  // oh well.
    }

    বাবে (পূর্ণাঙ্ক i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    পূর্ণাঙ্ক total_buttons = 0;
    বাবে (পূর্ণাঙ্ক i = 0; i < dev->অঙ্ক_classes; i++) {
        ধ্রুৱ XIAnyClassInfo *classinfo = dev->classes[i];
        যদি (classinfo->type == XIButtonClass) {
            ধ্রুৱ XIButtonClassInfo *button_classinfo = (ধ্রুৱ XIButtonClassInfo *)classinfo;
            total_buttons += button_classinfo->অঙ্ক_buttons;
        } অন্যথা যদি (classinfo->type == XIValuatorClass) {
            ধ্রুৱ XIValuatorClassInfo *val_classinfo = (ধ্রুৱ XIValuatorClassInfo *)classinfo;
            ধ্রুৱ Sint8 valuator_nr = val_classinfo->সংখ্যা_2;
            ধ্রুৱ Atom vname = val_classinfo->label;
            ধ্রুৱ ভিন্ন min = (ভিন্ন)val_classinfo->min;
            ধ্রুৱ ভিন্ন max = (ভিন্ন)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_গুনতি;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            যদি (vname == data->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } অন্যথা যদি (vname == data->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } অন্যথা যদি (vname == data->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } অন্যথা {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            যদি (use_this_axis) {
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

    ধ্রুৱ bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.অঙ্ক_buttons = total_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    যদি (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool in_proximity = false;
    যদি (!X11_XInput2PenIsInProximity(_this, dev->deviceid, &in_proximity)) {
        in_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_AddPenDevice(0, dev->name, রিক্ত, &peninfo, handle, in_proximity);
    যদি (!handle->pen) {
        SDL_free(handle);
        ঘূৰাই রিক্ত;
    }

    ঘূৰাই handle;
}

X11_PenHandle *X11_MaybeAddPenByDeviceID(SDL_VideoDevice *_this, পূর্ণাঙ্ক deviceid)
{
    যদি (X11_Xinput2IsInitialized()) {
        SDL_VideoData *data = _this->internal;
        পূর্ণাঙ্ক অঙ্ক_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, deviceid, &অঙ্ক_device_info);
        যদি (device_info) {
            SDL_assert(অঙ্ক_device_info == 1);
            X11_PenHandle *handle = X11_MaybeAddPen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            ঘূৰাই handle;
        }
    }
    ঘূৰাই রিক্ত;
}

শূন্য X11_RemovePenByDeviceID(পূর্ণাঙ্ক deviceid)
{
    X11_PenHandle *handle = X11_FindPenByDeviceID(deviceid);
    যদি (handle) {
        SDL_RemovePenDevice(0, রিক্ত, handle->pen);
        SDL_free(handle);
    }
}

শূন্য X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_Window *window, পূর্ণাঙ্ক deviceid)
{
    bool in_proximity;
    X11_PenHandle *pen = X11_FindPenByDeviceID(deviceid);
    যদি (pen && X11_XInput2PenIsInProximity(_this, deviceid, &in_proximity)) {
        SDL_SendPenProximity(0, pen->pen, window, in_proximity, in_proximity);
    }
}

শূন্য X11_InitPen(SDL_VideoDevice *_this)
{
    যদি (!X11_Xinput2IsInitialized()) {
        ঘূৰাই;  // we need XIQueryDevice() for this.
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
    পূর্ণাঙ্ক অঙ্ক_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(data->display, XIAllDevices, &অঙ্ক_device_info);
    যদি (device_info) {
        বাবে (পূর্ণাঙ্ক i = 0; i < অঙ্ক_device_info; i++) {
            X11_MaybeAddPen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

স্থির শূন্য X11_FreePenHandle(SDL_PenID instance_id, শূন্য *handle, শূন্য *userdata)
{
    SDL_free(handle);
}

শূন্য X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, রিক্ত);
}

স্থির শূন্য X11_XInput2NormalizePenAxes(ধ্রুৱ X11_PenHandle *pen, ভিন্ন *coords)
{
    // Normalise axes
    বাবে (পূর্ণাঙ্ক axis = 0; axis < SDL_PEN_AXIS_গুনতি; ++axis) {
        ধ্রুৱ পূর্ণাঙ্ক valuator = pen->valuator_for_axis[axis];
        যদি (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            অনুৱর্ত;
        }

        ভিন্ন মান = coords[axis];
        ধ্রুৱ ভিন্ন min = pen->axis_min[axis];
        ধ্রুৱ ভিন্ন max = pen->axis_max[axis];

        যদি (axis == SDL_PEN_AXIS_SLIDER) {
            মান += pen->slider_bias;
        }

        // min ... 0 ... max
        যদি (min < 0.0) {
            // Normalise so that 0 remains 0.0
            যদি (মান < 0) {
                মান = মান / (-min);
            } অন্যথা {
                যদি (max == 0.0f) {
                    মান = 0.0f;
                } অন্যথা {
                    মান = মান / max;
                }
            }
        } অন্যথা {
            // 0 ... min ... max
            // including 0.0 = min
            যদি (max == 0.0f) {
                মান = 0.0f;
            } অন্যথা {
                মান = (মান - min) / max;
            }
        }

        ৱিকল্প (axis) {
            পক্ষ SDL_PEN_AXIS_XTILT:
            পক্ষ SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                ভঙ্গ;

            পক্ষ SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                মান *= 180.0f;
                মান += pen->rotation_bias;

                // handle simple over/underflow
                যদি (মান >= 180.0f) {
                    মান -= 360.0f;
                } অন্যথা যদি (মান < -180.0f) {
                    মান += 360.0f;
                }
                ভঙ্গ;

            স্ৱভাৱ:
                ভঙ্গ;
        }

        coords[axis] = মান;
    }
}

শূন্য X11_PenAxesFromValuators(ধ্রুৱ X11_PenHandle *pen,
                              ধ্রুৱ দ্ৱিগুণ *প্ৰবেশ_মানসমূহ, ধ্রুৱ unsigned ৱর্ণ *mask, পূর্ণাঙ্ক mask_len,
                              ভিন্ন axis_মানসমূহ[SDL_PEN_AXIS_গুনতি])
{
    বাবে (পূর্ণাঙ্ক i = 0; i < SDL_PEN_AXIS_গুনতি; i++) {
        ধ্রুৱ পূর্ণাঙ্ক valuator = pen->valuator_for_axis[i];
        যদি ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= mask_len * 8) || !(XIMaskIsSet(mask, valuator))) {
            axis_মানসমূহ[i] = 0.0f;
        } অন্যথা {
            axis_মানসমূহ[i] = (ভিন্ন)প্ৰবেশ_মানসমূহ[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_মানসমূহ);
}

#অন্যথা

শূন্য X11_InitPen(SDL_VideoDevice *_this)
{
    (শূন্য) _this;
}

শূন্য X11_QuitPen(SDL_VideoDevice *_this)
{
    (শূন্য) _this;
}

#endif // SDL_VIDEO_DRIVER_X11_XINPUT2

