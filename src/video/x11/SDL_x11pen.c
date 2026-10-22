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
#అన్తర్భావ "../../SDL_internal.h"

#అన్తర్భావ "../../events/SDL_pen_c.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "SDL_x11pen.h"
#అన్తర్భావ "SDL_x11video.h"
#అన్తర్భావ "SDL_x11xinput2.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_X11_XINPUT2

// Does this device have a valuator for pressure sensitivity?
స్థిర bool X11_XInput2DeviceIsPen(SDL_VideoDevice *_this, స్థిరరాశి XIDeviceInfo *dev)
{
    స్థిరరాశి SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    కొరకు (పూర్ణాంకం i = 0; i < dev->అంకె_classes; i++) {
        స్థిరరాశి XIAnyClassInfo *classinfo = dev->classes[i];
        ఒకవేళ (classinfo->type == XIValuatorClass) {
            స్థిరరాశి XIValuatorClassInfo *val_classinfo = (స్థిరరాశి XIValuatorClassInfo *)classinfo;
            ఒకవేళ (val_classinfo->label == దత్తాంశం->atoms.pen_atom_abs_pressure) {
                తిరిగి true;
            }
        }
    }

    తిరిగి false;
}

// Heuristically determines if device is an eraser
స్థిర bool X11_XInput2PenIsEraser(SDL_VideoDevice *_this, పూర్ణాంకం deviceid, అక్షరం *devicename)
{
    #నిర్వచించు PEN_ERASER_NAME_ట్యాగ్  "eraser" // String constant to identify erasers
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    ఒకవేళ (దత్తాంశం->atoms.pen_atom_wacom_tool_type != None) {
        Atom type_return;
        పూర్ణాంకం format_return;
        గుర్తులేని దీర్ఘ అంకె_వస్తువులు_return;
        గుర్తులేని దీర్ఘ బైట్లు_after_return;
        గుర్తులేని అక్షరం *tooltype_name_info = ఖాళీ;

        // Try Wacom-specific method
        ఒకవేళ (Success == X11_XIGetProperty(దత్తాంశం->display, deviceid,
                                         దత్తాంశం->atoms.pen_atom_wacom_tool_type,
                                         0, 32, False,
                                         AnyPropertyType, &type_return, &format_return,
                                         &అంకె_వస్తువులు_return, &బైట్లు_after_return,
                                         &tooltype_name_info) &&
            tooltype_name_info != ఖాళీ && అంకె_వస్తువులు_return > 0) {

            bool ఫలితం = false;
            అక్షరం *tooltype_name = ఖాళీ;

            ఒకవేళ (type_return == XA_ATOM) {
                // Atom instead of string?  Un-intern
                Atom atom = *((Atom *)tooltype_name_info);
                ఒకవేళ (atom != None) {
                    tooltype_name = X11_XGetAtomName(దత్తాంశం->display, atom);
                }
            } లేకపోతే ఒకవేళ (type_return == XA_STRING && format_return == 8) {
                tooltype_name = (అక్షరం *)tooltype_name_info;
            }

            ఒకవేళ (tooltype_name) {
                ఒకవేళ (SDL_strcasecmp(tooltype_name, PEN_ERASER_NAME_ట్యాగ్) == 0) {
                    ఫలితం = true;
                }
                ఒకవేళ (tooltype_name != (అక్షరం *)tooltype_name_info) {
                    X11_XFree(tooltype_name_info);
                }
                X11_XFree(tooltype_name);

                తిరిగి ఫలితం;
            }
        }
    }

    // Non-Wacom device?

    /* We assume that a device is an eraser if its name contains the string "eraser".
     * Unfortunately there doesn't seem to be a clean way to distinguish these cases (as of 2022-03). */
    తిరిగి (SDL_strcasestr(devicename, PEN_ERASER_NAME_ట్యాగ్)) ? true : false;
}

// Read out an integer property and store into a preallocated Sint32 array, extending 8 and 16 bit values suitably.
// Returns number of Sint32s written (<= max_words), or 0 on error.
స్థిర size_t X11_XInput2PenGetIntProperty(SDL_VideoDevice *_this, పూర్ణాంకం deviceid, Atom property, Sint32 *dest, size_t max_పదాలు)
{
    స్థిరరాశి SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Atom type_return;
    పూర్ణాంకం format_return;
    గుర్తులేని దీర్ఘ అంకె_వస్తువులు_return;
    గుర్తులేని దీర్ఘ బైట్లు_after_return;
    గుర్తులేని అక్షరం *output;

    ఒకవేళ (property == None) {
        తిరిగి 0;
    }

    ఒకవేళ (Success != X11_XIGetProperty(దత్తాంశం->display, deviceid,
                                     property,
                                     0, max_పదాలు, False,
                                     XA_INTEGER, &type_return, &format_return,
                                     &అంకె_వస్తువులు_return, &బైట్లు_after_return,
                                     &output) ||
        అంకె_వస్తువులు_return == 0 || output == ఖాళీ) {
        తిరిగి 0;
    }

    ఒకవేళ (type_return == XA_INTEGER) {
        పూర్ణాంకం k;
        స్థిరరాశి పూర్ణాంకం గమ్యం_copy = SDL_min(max_పదాలు, అంకె_వస్తువులు_return);

        ఒకవేళ (format_return == 8) {
            Sint8 *numdata = (Sint8 *)output;
            కొరకు (k = 0; k < గమ్యం_copy; ++k) {
                dest[k] = numdata[k];
            }
        } లేకపోతే ఒకవేళ (format_return == 16) {
            Sint16 *numdata = (Sint16 *)output;
            కొరకు (k = 0; k < గమ్యం_copy; ++k) {
                dest[k] = numdata[k];
            }
        } లేకపోతే {
            SDL_memcpy(dest, output, పరిమాణం(Sint32) * గమ్యం_copy);
        }
        X11_XFree(output);
        తిరిగి గమ్యం_copy;
    }

    తిరిగి 0; // type mismatch
}

// Identify Wacom devices (if true is returned) and extract their device type and serial IDs
స్థిర bool X11_XInput2PenWacomDeviceID(SDL_VideoDevice *_this, పూర్ణాంకం deviceid, Uint32 *wacom_devicetype_id, Uint32 *wacom_serial)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Sint32 serial_id_buf[3];
    పూర్ణాంకం ఫలితం;

    ఒకవేళ ((ఫలితం = X11_XInput2PenGetIntProperty(_this, deviceid, దత్తాంశం->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 3)) == 3) {
        *wacom_devicetype_id = serial_id_buf[2];
        *wacom_serial = serial_id_buf[1];
        తిరిగి true;
    }

    *wacom_devicetype_id = *wacom_serial = 0;
    తిరిగి false;
}

// Check if a Wacom device is in proximity of the tablet
స్థిర bool X11_XInput2_Pen_Is_లోపల_Proximity(SDL_VideoDevice *_this, పూర్ణాంకం deviceid, bool *లోపల_proximity)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Sint32 serial_id_buf[5];
    ఒకవేళ (X11_XInput2PenGetIntProperty(_this, deviceid, దత్తాంశం->atoms.pen_atom_wacom_serial_ids, serial_id_buf, 5) == 5) {
        *లోపల_proximity = serial_id_buf[4] != 0 || serial_id_buf[3] != 0;
        తిరిగి true;
    }
    తిరిగి false;
}


రకనిర్వచనం నిర్మాణం కనుగొను_Pen_By_Device_IDData
{
    పూర్ణాంకం x11_deviceid;
    శూన్య *handle;
} కనుగొను_Pen_By_Device_IDData;

స్థిర bool కనుగొను_Pen_By_Device_ID(శూన్య *handle, శూన్య *userdata)
{
    స్థిరరాశి X11_PenHandle *x11_handle = (స్థిరరాశి X11_PenHandle *) handle;
    కనుగొను_Pen_By_Device_IDData *దత్తాంశం = (కనుగొను_Pen_By_Device_IDData *) userdata;
    ఒకవేళ (x11_handle->x11_deviceid != దత్తాంశం->x11_deviceid) {
        తిరిగి false;
    }
    దత్తాంశం->handle = handle;
    తిరిగి true;
}

X11_PenHandle *X11_కనుగొను_Pen_By_Device_ID(పూర్ణాంకం deviceid)
{
    కనుగొను_Pen_By_Device_IDData దత్తాంశం;
    దత్తాంశం.x11_deviceid = deviceid;
    దత్తాంశం.handle = ఖాళీ;
    SDL_కనుగొను_Pen_By_Callback(కనుగొను_Pen_By_Device_ID, &దత్తాంశం);
    తిరిగి (X11_PenHandle *) దత్తాంశం.handle;
}

స్థిర X11_PenHandle *X11_Maybe_కూడు_Pen(SDL_VideoDevice *_this, స్థిరరాశి XIDeviceInfo *dev)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    SDL_PenCapabilityFlags capabilities = 0;
    X11_PenHandle *handle = ఖాళీ;

    ఒకవేళ ((dev->use != XISlave_సూచిక && (dev->use != XIFloatingSlave)) || dev->enabled == 0 || !X11_XInput2DeviceIsPen(_this, dev)) {
        తిరిగి ఖాళీ;  // Only track physical devices that are enabled and look like pens
    } లేకపోతే ఒకవేళ ((handle = X11_కనుగొను_Pen_By_Device_ID(dev->deviceid)) != ఖాళీ) {
        తిరిగి handle;  // already have this pen, skip it.
    } లేకపోతే ఒకవేళ ((handle = SDL_calloc(1, పరిమాణం(*handle))) == ఖాళీ) {
        తిరిగి ఖాళీ;  // oh well.
    }

    కొరకు (పూర్ణాంకం i = 0; i < SDL_arraysize(handle->valuator_for_axis); i++) {
        handle->valuator_for_axis[i] = SDL_X11_PEN_AXIS_VALUATOR_MISSING;  // until proven otherwise
    }

    పూర్ణాంకం మొత్తం_buttons = 0;
    కొరకు (పూర్ణాంకం i = 0; i < dev->అంకె_classes; i++) {
        స్థిరరాశి XIAnyClassInfo *classinfo = dev->classes[i];
        ఒకవేళ (classinfo->type == XIButtonClass) {
            స్థిరరాశి XIButtonClassInfo *button_classinfo = (స్థిరరాశి XIButtonClassInfo *)classinfo;
            మొత్తం_buttons += button_classinfo->అంకె_buttons;
        } లేకపోతే ఒకవేళ (classinfo->type == XIValuatorClass) {
            స్థిరరాశి XIValuatorClassInfo *val_classinfo = (స్థిరరాశి XIValuatorClassInfo *)classinfo;
            స్థిరరాశి Sint8 valuator_nr = val_classinfo->సంఖ్య_2;
            స్థిరరాశి Atom vname = val_classinfo->label;
            స్థిరరాశి దశాంశం min = (దశాంశం)val_classinfo->min;
            స్థిరరాశి దశాంశం max = (దశాంశం)val_classinfo->max;
            bool use_this_axis = true;
            SDL_PenAxis axis = SDL_PEN_AXIS_లెక్క;

            // afaict, SDL_PEN_AXIS_DISTANCE is never reported by XInput2 (Wayland can offer it, though)
            ఒకవేళ (vname == దత్తాంశం->atoms.pen_atom_abs_pressure) {
                axis = SDL_PEN_AXIS_PRESSURE;
            } లేకపోతే ఒకవేళ (vname == దత్తాంశం->atoms.pen_atom_abs_tilt_x) {
                axis = SDL_PEN_AXIS_XTILT;
            } లేకపోతే ఒకవేళ (vname == దత్తాంశం->atoms.pen_atom_abs_tilt_y) {
                axis = SDL_PEN_AXIS_YTILT;
            } లేకపోతే {
                use_this_axis = false;
            }

            // !!! FIXME: there are wacom-specific hacks for getting SDL_PEN_AXIS_(ROTATION|SLIDER) on some devices, but for simplicity, we're skipping all that for now.

            ఒకవేళ (use_this_axis) {
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

    స్థిరరాశి bool is_eraser = X11_XInput2PenIsEraser(_this, dev->deviceid, dev->name);
    Uint32 wacom_devicetype_id = 0;
    Uint32 wacom_serial = 0;
    X11_XInput2PenWacomDeviceID(_this, dev->deviceid, &wacom_devicetype_id, &wacom_serial);

    SDL_PenInfo peninfo;
    SDL_zero(peninfo);
    peninfo.capabilities = capabilities;
    peninfo.max_tilt = -1;
    peninfo.wacom_id = wacom_devicetype_id;
    peninfo.అంకె_buttons = మొత్తం_buttons;
    peninfo.subtype = is_eraser ? SDL_PEN_TYPE_ERASER : SDL_PEN_TYPE_PEN;
    ఒకవేళ (is_eraser) {
        peninfo.capabilities |= SDL_PEN_CAPABILITY_ERASER;
    }

    handle->is_eraser = is_eraser;
    handle->x11_deviceid = dev->deviceid;

    bool లోపల_proximity = false;
    ఒకవేళ (!X11_XInput2_Pen_Is_లోపల_Proximity(_this, dev->deviceid, &లోపల_proximity)) {
        లోపల_proximity = true;  // just say it's in proximity if we can't detect this state.
    }

    handle->pen = SDL_కూడు_Pen_Device(0, dev->name, ఖాళీ, &peninfo, handle, లోపల_proximity);
    ఒకవేళ (!handle->pen) {
        SDL_free(handle);
        తిరిగి ఖాళీ;
    }

    తిరిగి handle;
}

X11_PenHandle *X11_Maybe_కూడు_Pen_By_Device_ID(SDL_VideoDevice *_this, పూర్ణాంకం deviceid)
{
    ఒకవేళ (X11_Xinput2IsInitialized()) {
        SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
        పూర్ణాంకం అంకె_device_info = 0;
        XIDeviceInfo *device_info = X11_XIQueryDevice(దత్తాంశం->display, deviceid, &అంకె_device_info);
        ఒకవేళ (device_info) {
            SDL_assert(అంకె_device_info == 1);
            X11_PenHandle *handle = X11_Maybe_కూడు_Pen(_this, device_info);
            X11_XIFreeDeviceInfo(device_info);
            తిరిగి handle;
        }
    }
    తిరిగి ఖాళీ;
}

శూన్య X11_RemovePenByDeviceID(పూర్ణాంకం deviceid)
{
    X11_PenHandle *handle = X11_కనుగొను_Pen_By_Device_ID(deviceid);
    ఒకవేళ (handle) {
        SDL_RemovePenDevice(0, ఖాళీ, handle->pen);
        SDL_free(handle);
    }
}

శూన్య X11_NotifyPenProximityChange(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, పూర్ణాంకం deviceid)
{
    bool లోపల_proximity;
    X11_PenHandle *pen = X11_కనుగొను_Pen_By_Device_ID(deviceid);
    ఒకవేళ (pen && X11_XInput2_Pen_Is_లోపల_Proximity(_this, deviceid, &లోపల_proximity)) {
        SDL_SendPenProximity(0, pen->pen, కిటికీ, లోపల_proximity, లోపల_proximity);
    }
}

శూన్య X11_InitPen(SDL_VideoDevice *_this)
{
    ఒకవేళ (!X11_Xinput2IsInitialized()) {
        తిరిగి;  // we need XIQueryDevice() for this.
    }

    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    #నిర్వచించు LOOKUP_PEN_ATOM(X) X11_XInternAtom(దత్తాంశం->display, X, False)
    దత్తాంశం->atoms.pen_atom_device_లబ్ధం_id = LOOKUP_PEN_ATOM("Device Product ID");
    దత్తాంశం->atoms.pen_atom_wacom_serial_ids = LOOKUP_PEN_ATOM("Wacom Serial IDs");
    దత్తాంశం->atoms.pen_atom_wacom_tool_type = LOOKUP_PEN_ATOM("Wacom Tool Type");
    దత్తాంశం->atoms.pen_atom_abs_pressure = LOOKUP_PEN_ATOM("Abs Pressure");
    దత్తాంశం->atoms.pen_atom_abs_tilt_x = LOOKUP_PEN_ATOM("Abs Tilt X");
    దత్తాంశం->atoms.pen_atom_abs_tilt_y = LOOKUP_PEN_ATOM("Abs Tilt Y");
    #నిర్వచనం_రద్దు LOOKUP_PEN_ATOM

    // Do an initial check on devices. After this, we'll add/remove individual pens when XI_HierarchyChanged events alert us.
    పూర్ణాంకం అంకె_device_info = 0;
    XIDeviceInfo *device_info = X11_XIQueryDevice(దత్తాంశం->display, XIAllDevices, &అంకె_device_info);
    ఒకవేళ (device_info) {
        కొరకు (పూర్ణాంకం i = 0; i < అంకె_device_info; i++) {
            X11_Maybe_కూడు_Pen(_this, &device_info[i]);
        }
        X11_XIFreeDeviceInfo(device_info);
    }
}

స్థిర శూన్య X11_FreePenHandle(SDL_PenID instance_id, శూన్య *handle, శూన్య *userdata)
{
    SDL_free(handle);
}

శూన్య X11_QuitPen(SDL_VideoDevice *_this)
{
    SDL_RemoveAllPenDevices(X11_FreePenHandle, ఖాళీ);
}

స్థిర శూన్య X11_XInput2NormalizePenAxes(స్థిరరాశి X11_PenHandle *pen, దశాంశం *coords)
{
    // Normalise axes
    కొరకు (పూర్ణాంకం axis = 0; axis < SDL_PEN_AXIS_లెక్క; ++axis) {
        స్థిరరాశి పూర్ణాంకం valuator = pen->valuator_for_axis[axis];
        ఒకవేళ (valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) {
            కొనసాగు;
        }

        దశాంశం విలువ = coords[axis];
        స్థిరరాశి దశాంశం min = pen->axis_min[axis];
        స్థిరరాశి దశాంశం max = pen->axis_max[axis];

        ఒకవేళ (axis == SDL_PEN_AXIS_SLIDER) {
            విలువ += pen->slider_bias;
        }

        // min ... 0 ... max
        ఒకవేళ (min < 0.0) {
            // Normalise so that 0 remains 0.0
            ఒకవేళ (విలువ < 0) {
                విలువ = విలువ / (-min);
            } లేకపోతే {
                ఒకవేళ (max == 0.0f) {
                    విలువ = 0.0f;
                } లేకపోతే {
                    విలువ = విలువ / max;
                }
            }
        } లేకపోతే {
            // 0 ... min ... max
            // including 0.0 = min
            ఒకవేళ (max == 0.0f) {
                విలువ = 0.0f;
            } లేకపోతే {
                విలువ = (విలువ - min) / max;
            }
        }

        ఎంపిక (axis) {
            స్థితి SDL_PEN_AXIS_XTILT:
            స్థితి SDL_PEN_AXIS_YTILT:
                //if (peninfo->info.max_tilt > 0.0f) {
                //    value *= peninfo->info.max_tilt; // normalize to physical max
                //}
                ఆపు;

            స్థితి SDL_PEN_AXIS_ROTATION:
                // normalised to -1..1, so let's convert to degrees
                విలువ *= 180.0f;
                విలువ += pen->rotation_bias;

                // handle simple over/underflow
                ఒకవేళ (విలువ >= 180.0f) {
                    విలువ -= 360.0f;
                } లేకపోతే ఒకవేళ (విలువ < -180.0f) {
                    విలువ += 360.0f;
                }
                ఆపు;

            అప్రమేయ:
                ఆపు;
        }

        coords[axis] = విలువ;
    }
}

శూన్య X11_PenAxesFromValuators(స్థిరరాశి X11_PenHandle *pen,
                              స్థిరరాశి ద్విగుణ *ఆదానం_విలువలు, స్థిరరాశి గుర్తులేని అక్షరం *ముసుగు, పూర్ణాంకం ముసుగు_len,
                              దశాంశం axis_విలువలు[SDL_PEN_AXIS_లెక్క])
{
    కొరకు (పూర్ణాంకం i = 0; i < SDL_PEN_AXIS_లెక్క; i++) {
        స్థిరరాశి పూర్ణాంకం valuator = pen->valuator_for_axis[i];
        ఒకవేళ ((valuator == SDL_X11_PEN_AXIS_VALUATOR_MISSING) || (valuator >= ముసుగు_len * 8) || !(XIMask_Is_సమితి(ముసుగు, valuator))) {
            axis_విలువలు[i] = 0.0f;
        } లేకపోతే {
            axis_విలువలు[i] = (దశాంశం)ఆదానం_విలువలు[valuator];
        }
    }
    X11_XInput2NormalizePenAxes(pen, axis_విలువలు);
}

#లేకపోతే

శూన్య X11_InitPen(SDL_VideoDevice *_this)
{
    (శూన్య) _this;
}

శూన్య X11_QuitPen(SDL_VideoDevice *_this)
{
    (శూన్య) _this;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_X11_XINPUT2

