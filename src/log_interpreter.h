/* 
 * Copyright (C) 2013  Nicholas Gill
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * log_interpreter.h
 *
 *  Created on: 2014-12-09
 *      Author: nicholas
 */

#ifndef LOG_INTERPRETER_H_
#define LOG_INTERPRETER_H_
#include "rs274ngc.hh"

class log_interpreter : public rs274ngc
{
private:
	virtual void interp_init();

	// Logging
	int               _line_number = 1;

	// State

	Plane       _active_plane = Plane::XY;
	int               _active_slot = 1;
	double            _feed_rate = 0.0;
	int               _flood = 0;
	int               _mist = 0;
	Units       _length_unit_type = Units::Metric;
	Motion _motion_mode = Motion::Continuous;

	Position probe_pos;
	Position origin_pos;
	Position program_pos;

	double            _spindle_speed;
	Direction   _spindle_turning;
	double            _traverse_rate;

	// Data

	/* Provided by interpreter, rs274ngc will
	 * call tool(n) with n up to tool_max. */
	int                      _tool_max = 68;
	Tool         _tools[CANON_TOOL_MAX];

	char                     _parameter_file_name[100];
private:

	void print_nc_line_number();

	virtual void offset_origin(const Position& pos);
	virtual void units(Units u);
	virtual void rapid_rate(double rate);
	virtual void rapid(const Position& pos);
	virtual void feed_rate(double rate);
	virtual void feed_reference(FeedReference reference);
	virtual void motion_mode(Motion mode);
	virtual void plane(Plane pl);
	virtual void cutter_radius_comp(double radius);
	virtual void cutter_radius_comp_start(Side direction);
	virtual void cutter_radius_comp_stop();
	virtual void speed_feed_sync_start();
	virtual void speed_feed_sync_stop();
	virtual void arc(double end0, double end1, double axis0, double axis1, int rotation, double end_point, double a, double b, double c);
	virtual void linear(const Position& pos);
	virtual void probe(const Position& pos);
	virtual void dwell(double seconds);
	virtual void spindle_start_clockwise();
	virtual void spindle_start_counterclockwise();
	virtual void spindle_speed(double r);
	virtual void spindle_stop();
	virtual void spindle_orient(double orientation, Direction direction);
	virtual void tool_length_offset(double length);
	virtual void tool_change(int slot);
	virtual void tool_select(int i);
	virtual void axis_clamp(Axis axis);
	virtual void comment(const char *s);
	virtual void feed_override_disable();
	virtual void speed_override_disable();
	virtual void feed_override_enable();
	virtual void speed_override_enable();
	virtual void coolant_flood_off();
	virtual void coolant_flood_on();
	virtual void message(const char *s);
	virtual void coolant_mist_off();
	virtual void coolant_mist_on();
	virtual void pallet_shuttle();
	virtual void probe_off();
	virtual void probe_on();
	virtual void axis_unclamp(Axis axis);
	virtual void program_stop();
	virtual void program_optional_stop();
	virtual void program_end();
	virtual double feed_rate() const;
	virtual bool coolant_flood() const;
	virtual Units units() const;
	virtual bool coolant_mist() const;
	virtual Motion motion_mode() const;
	virtual void get_parameter_filename(char* filename, size_t max_size) const;
	virtual Plane plane() const;
	virtual Position current_position() const;
	virtual Position probe_position() const;
	virtual double probe_value() const;
	virtual bool queue_empty() const;
	virtual double spindle_speed() const;
	virtual Direction spindle_state() const;
	virtual int tool_slot() const;
	virtual unsigned int tool_max() const;
	virtual Tool tool(int pocket) const;
	virtual double rapid_rate() const;

public:
	log_interpreter();
	virtual ~log_interpreter() = default;
};

#endif /* LOG_INTERPRETER_H_ */
