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
#شامل "../../SDL_internal.h"

#شامل "../../events/SDL_pen_c.h"
#شامل "../SDL_sysvideo.h"
#شامل "SDL_x11pen.h"
#شامل "SDL_x11video.h"
#شامل "SDL_x11xinput2.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
ساکن bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, ثابت XIDeviceInfo *dev)
{
    ثابت SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    برائے (صحیح i = 0; i < dev->عدد_classes; i++) {
        ثابت XIAnyClassInfo *classinfo = dev->classes[i];
        اگر (classinfo->type == XIValuatorClass) {
            ثابت XIValuatorClassInfo *val_classinfo = (ثابت XIValuatorClassInfo *)classinfo;
            اگر (val_classinfo->label == ڈیٹا->atoms.pen_atom_abs_pressure) {
                واپس true;
            }
        }
    }

    واپس false;
}

// Heuristically determines if device is an eraser
ساکن bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, صحیح deviceid, حرف *devicename)
{
    #تعریف_کرو PEN_ERASER_NAME_لیبل  "eraser" // String constant to identify erasers
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    اگر (ڈیٹا->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        صحیح format_return;
        غیرعلامتی طویل عدد_اشیاء_return;
        غیرعلامتی طویل بائٹیں_after_return;
        غیرعلامتی حرف *tooltype_name_info = تہی;

        // Try Wacom-specific method
        اگر (Success == X11_XIGetProperty(ڈیٹا->display, deviceid,
                                         ڈیٹا->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &عدد_اشیاء_return, &بائٹیں_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != تہی && عدد_اشیاء_return > 0) {

            bool نتیجہ = false;
            حرف *tooltype_name = تہی;

            اگر (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                اگر (atom != None) {
                    tooltype_name = X11_XGetAtomName(ڈیٹا->display, atom);
                }
            } ورنہ اگر (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (حرف *)tooltype_name_info;
            }

            اگر (tooltype_name) {
                اگر (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_لیبل) == 0) {
                    نتیجہ = true;
                }
                اگر (tooltype_name != (حرف *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                واپس نتیجہ;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    واپس (SDL_strcasestr(devicename, PEN_ERASER_NAME_لیبل)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
ساکن size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, صحیح deviceid, Atom property, Sint32 *dest, size_t max_الفاظ)
{
    ثابت SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    Atom type_return;
    صحیح format_return;
    غیرعلامتی طویل عدد_اشیاء_return;
    غیرعلامتی طویل بائٹیں_after_return;
    غیرعلامتی حرف *output;

    اگر (property == None) {
        واپس 0;
    }

    اگر (Success != X11_XIGetProperty(ڈیٹا->display, deviceid,
                                     property,
                                     0, max_الفاظ, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &عدد_اشیاء_return, &بائٹیں_after_return,
                                     &output) ||
        عدد_اشیاء_return == 0 || output == تہی) {
        واپس 0;
    }

    اگر (type_return == XA_INTEGER) {
        صحیح k;
        ثابت صحیح مقصد_copy = SDL_min(max_الفاظ, عدد_اشیاء_return);

        اگر (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            برائے (k = 0; k < مقصد_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ورنہ اگر (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            برائے (k = 0; k < مقصد_copy; ++k) {
                dest[k] = numdata[k];
            }
        } ورنہ {
            SDL_memcpy(dest, output, حجم(Sint32) * مقصد_copy);
        }
        X11_XFree(output);
        واپس مقصد_copy;
    }

    واپس 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
ساکن bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, صحیح deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    Sint32 serial_id_buf[3];
    صحیح نتیجہ;

    اگر ((نتیجہ = X11_XInput2PenGetIntProperty(_this, deviceid, ڈیٹا->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        واپس true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    واپس false;
}

// Check if a Wacom device is in proximity of the tablet
ساکن bool X11_XInput2_Pen_Is_اندر_Proximity(SDL_VideoDevice *_this, صحیح deviceid, bool *اندر_proximity)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    Sint32 serial_id_buf[5];
    اگر (X11_XInput2PenGetIntProperty(_this, deviceid, ڈیٹا->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *اندر_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        واپس true;
    }
    واپس false;
}


قسمتعریف ساخت ڈھونڈو_Pen_By_Device_IDData
{
    صحیح x11_deviceid;
    خالی *handle;
} ڈھونڈو_Pen_By_Device_IDData;

ساکن bool ڈھونڈو_Pen_By_Device_ID(خالی *handle, خالی *userdata)
{
    ثابت X11_PenHandle *x11_handle = (ثابت X11_PenHandle *) handle;
    ڈھونڈو_Pen_By_Device_IDData *ڈیٹا = (ڈھونڈو_Pen_By_Device_IDData *) userdata;
    اگر (x11_handle->x11_deviceid != ڈیٹا->x11_deviceid) {
        واپس false;
    }
    ڈیٹا->handle = handle;
    واپس true;
}

X11_PenHandle *X11_ڈھونڈو_Pen_By_Device_ID(صحیح deviceid)
{
    ڈھونڈو_Pen_By_Device_IDData ڈیٹا;
    ڈیٹا.x11_deviceid = deviceid;
    ڈیٹا.handle = تہی;
    SDL_ڈھونڈو_Pen_By_Callback(ڈھونڈو_Pen_By_Device_ID, &ڈیٹا);
    واپس (X11_PenHandle *) ڈیٹا.handle;
}

ساکن X11_PenHandle *X11_Maybe_جوڑو_Pen(SDL_VideoDevice *_this, ثابت XIDeviceInfo *dev)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = تہی;

    اگر ((dev->use != XISlave_اشارہ_گر && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        واپس تہی;  // Only track physical devices that are enabled and look like pens
    } ورنہ اگر ((handle = X11_ڈھونڈو_Pen_By_Device_ID(dev->deviceid)) != تہی) {
        واپس handle;  // already have this pen, skip it.
    } ورنہ اگر ((handle = SDL_calloc(1, حجم(*handle))) == تہی) {
        واپس تہی;  // oh well.
    }

    برائے (صحیح i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    صحیح کل_buttons = 0;
    برائے (صحیح i = 0; i < dev->عدد_classes; i++) {
        ثابت XIAnyClassInfo *classinfo = dev->classes[i];
        اگر (classinfo->type == XIButtonClass) {
            ثابت XIButtonClassInfo *button_classinfo = (ثابت XIButtonClassInfo *)classinfo;
            کل_buttons += button_classinfo->عدد_buttons;
        } ورنہ اگر (classinfo->type == XIValuatorClass) {
            ثابت XIValuatorClassInfo *val_classinfo = (ثابت XIValuatorClassInfo *)classinfo;
            ثابت Sint8 valuator_nr = val_classinfo->نمبر_2;
            ثابت Atom vname = val_classinfo->label;
            ثابت اعشاری min = (اعشاری)val_classinfo->min;
            ثابت اعشاری max = (اعشاری)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_گنتی;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            اگر (vname == ڈیٹا->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } ورنہ اگر (vname == ڈیٹا->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } ورنہ اگر (vname == ڈیٹا->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } ورنہ {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            اگر (use_this_axis) {
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

    ثابت bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.عدد_buttons = کل_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    اگر (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool اندر_proximity = false;
    اگر (!X11_XInput2_Pen_Is_اندر_Proximity(_this, dev->deviceid, &اندر_proximity)) {
        اندر_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_جوڑو_Pen_Device(0, dev->name, تہی, &peninfo, handle, اندر_proximity);
    اگر (!handle->pen) {
        SDL_free(handle);
        واپس تہی;
    }

    واپس handle;
}

X11_PenHandle *X11_Maybe_جوڑو_Pen_By_Device_ID(SDL_VideoDevice *_this, صحیح deviceid)
{
    اگر (X11_Xinput2IsInitialized()) {
        SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
        صحیح عدد_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(ڈیٹا->display, deviceid, &عدد_device_info);
        اگر (device_info) {
            SDL_assert(عدد_device_info == 1);
            X11_PenHandle *handle = X11_Maybe_جوڑو_Pen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            واپس handle;
        }
    }
    واپس تہی;
}

خالی X11_RemovePenByDeviceID(صحیح deviceid)
{
    X11_PenHandle *handle = X11_ڈھونڈو_Pen_By_Device_ID(deviceid);
    اگر (handle) {
        SDL_RemovePenDevice(0, تہی, handle->pen);
        SDL_free(handle);
    }
}

خالی X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_کھڑکی *کھڑکی, صحیح deviceid)
{
    bool اندر_proximity;
    X11_PenHandle *pen = X11_ڈھونڈو_Pen_By_Device_ID(deviceid);
    اگر (pen && X11_XInput2_Pen_Is_اندر_Proximity(_this, deviceid, &اندر_proximity)) {
        SDL_SendPenProximity(0, pen->pen, کھڑکی, اندر_proximity, اندر_proximity);
    }
}

خالی X11_InitPen(SDL_VideoDevice *_this)
{
    اگر (!X11_Xinput2IsInitialized()) {
        واپس;  // we need XIQueryDevice() for this.
    }

    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    #تعریف_کرو LOOKUP_PEN_ATOM(X) X11_XInternAtom(ڈیٹا->display, X, False)
    ڈیٹا->atoms.pen_atom_device_حاصل_ضرب_id = LOOKUP_PEN_ATOM("Device Product ID");
    ڈیٹا->atoms.pen_atom_wacom_serial_ids = LOOKUP_PEN_ATOM("Wacom Serial IDs");
    ڈیٹا->atoms.pen_atom_wacom_tool_type = LOOKUP_PEN_ATOM("Wacom Tool Type");
    ڈیٹا->atoms.pen_atom_abs_pressure = LOOKUP_PEN_ATOM("Abs Pressure");
    ڈیٹا->atoms.pen_atom_abs_tilt_x = LOOKUP_PEN_ATOM("Abs Tilt X");
    ڈیٹا->atoms.pen_atom_abs_tilt_y = LOOKUP_PEN_ATOM("Abs Tilt Y");
    #تعریف_منسوخ LOOKUP_PEN_ATOM

    // Do an initial check on devices. After this, we'll add/remove individual pens when XI_HierarchyChanged events alert us.
    صحیح عدد_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(ڈیٹا->display, XIAllDevices, &عدد_device_info);
    اگر (device_info) {
        برائے (صحیح i = 0; i < عدد_device_info; i++) {
            X11_Maybe_جوڑو_Pen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

ساکن خالی X11_FreePenHandle(SDL_PenID instance_id, خالی *handle, خالی *userdata)
{
    SDL_free(handle);
}

خالی X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, تہی);
}

ساکن خالی X11_XInput2NormalizePenAxes(ثابت X11_PenHandle *pen, اعشاری *coords)
{
    // Normalise axes
    برائے (صحیح axis = 0; axis < SDL_PEN_AXIS_گنتی; ++axis) {
        ثابت صحیح valuator = pen->valuator_for_axis[axis];
        اگر (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            جاری;
        }

        اعشاری قدر = coords[axis];
        ثابت اعشاری min = pen->axis_min[axis];
        ثابت اعشاری max = pen->axis_max[axis];

        اگر (axis == SDL_PEN_AXIS_SLIDER) {
            قدر += pen->slider_bias;
        }

        // min ... 0 ... max
        اگر (min < 0.0) {
            // Normalise so that 0 remains 0.0
            اگر (قدر < 0) {
                قدر = قدر / (-min);
            } ورنہ {
                اگر (max == 0.0f) {
                    قدر = 0.0f;
                } ورنہ {
                    قدر = قدر / max;
                }
            }
        } ورنہ {
            // 0 ... min ... max
            // including 0.0 = min
            اگر (max == 0.0f) {
                قدر = 0.0f;
            } ورنہ {
                قدر = (قدر - min) / max;
            }
        }

        انتخاب (axis) {
            حالت SDL_PEN_AXIS_XTILT:
            حالت SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                توڑو;

            حالت SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                قدر *= 180.0f;
                قدر += pen->rotation_bias;

                // handle simple over/underflow
                اگر (قدر >= 180.0f) {
                    قدر -= 360.0f;
                } ورنہ اگر (قدر < -180.0f) {
                    قدر += 360.0f;
                }
                توڑو;

            طےشدہ:
                توڑو;
        }

        coords[axis] = قدر;
    }
}

خالی X11_PenAxesFromValuators(ثابت X11_PenHandle *pen,
                              ثابت دوہرا *داخلہ_اقدار, ثابت غیرعلامتی حرف *نقاب, صحیح نقاب_len,
                              اعشاری axis_اقدار[SDL_PEN_AXIS_گنتی])
{
    برائے (صحیح i = 0; i < SDL_PEN_AXIS_گنتی; i++) {
        ثابت صحیح valuator = pen->valuator_for_axis[i];
        اگر ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= نقاب_len * 8) || !(XIMask_Is_سیٹ(نقاب, valuator))) {
            axis_اقدار[i] = 0.0f;
        } ورنہ {
            axis_اقدار[i] = (اعشاری)داخلہ_اقدار[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_اقدار);
}

#ورنہ

خالی X11_InitPen(SDL_VideoDevice *_this)
{
    (خالی) _this;
}

خالی X11_QuitPen(SDL_VideoDevice *_this)
{
    (خالی) _this;
}

#اگر_ختم // SDL_VIDEO_DRIVER_X11_XINPUT2

