# Copyright (C) 1991-2007 Altera Corporation
# Your use of Altera Corporation's design tools, logic functions 
# and other software and tools, and its AMPP partner logic 
# functions, and any output files from any of the foregoing 
# (including device programming or simulation files), and any 
# associated documentation or information are expressly subject 
# to the terms and conditions of the Altera Program License 
# Subscription Agreement, Altera MegaCore Function License 
# Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by 
# Altera or its authorized distributors.  Please refer to the 
# applicable agreement for further details.

# Quartus II: Generate Tcl File for Project
# File: DreamTangle_HDL.tcl
# Generated on: Tue Nov 06 09:51:51 2007

# Load Quartus II Tcl Project package
package require ::quartus::project

set need_to_close_project 0
set make_assignments 1

# Check that the right project is open
if {[is_project_open]} {
	if {[string compare $quartus(project) "DreamTangle_HDL"]} {
		puts "Project DreamTangle_HDL is not open"
		set make_assignments 0
	}
} else {
	# Only open if not already open
	if {[project_exists DreamTangle_HDL]} {
		project_open -revision DreamTangle_HDL DreamTangle_HDL
	} else {
		project_new -revision DreamTangle_HDL DreamTangle_HDL
	}
	set need_to_close_project 1
}

# Make assignments
if {$make_assignments} {
	###############################################################
	#
	# Descriptions of Design Partition Assignments
	# --------------------------------------------
	#
	# PARTITION_HIERARCHY
	#
	#	This assignment can be used to define a new partition.
	#
	# PARTITION_NETLIST_TYPE
	#
	#	This assignment can be used to specify how a partition
	#	is compiled in the next compilation. It can take on one of
	#	the following values:
	#	
	#	SOURCE
	#		Directs the Compiler always to compile the design partition
	#		using the associated source files.
	#	
	#	POST_SYNTH
	#		Directs the Compiler to preserve the post-synthesis results
	#		for the design partition and to compile the design partition
	#		using the post-synthesis netlist, provided that the associated
	#		source files are unchanged since the previous synthesis. If a
	#		post-synthesis netlist does not exist, the design partition is
	#		compiled from the source files. Changes to analysis and synthesis
	#		assignments, however, do not cause the design partition to be
	#		recompiled.
	#	
	#	POST_FIT
	#		Directs the Compiler to preserve the post-fitting results for
	#		the design partition and to compile the design partition using
	#		the post-fit netlist, provided that the associated source files
	#		are unchanged since the previous fitting. If a post-fit netlist
	#		does not exist, the design partition is compiled from the source
	#		files or the post-synthesis netlist. Changes to Fitter assignments,
	#		however, do not cause the design partition to be recompiled.
	#	
	#	STRICT_POST_FIT
	#		Directs the Compiler to preserve the post-fitting results for
	#		the design partition and to compile the design partition using
	#		the post-fit netlist, ignoring any changes to the associated
	#		source files.
	#	
	#	IMPORTED
	#		Directs the Compiler to compile the design partition using a
	#		netlist imported from a Quartus II Exported Partition File.
	#
	#	IMPORT_BASED_POST_FIT
	#		Directs the Compiler to preserve the post-fitting results for
	#		the design partition and to compile the design partition using
	#		the post-fit netlist, provided that the associated imported netlist
	#		is unchanged since the previous fitting. If a post-fit netlist
	#		does not exist, the design partition is compiled from the imported
	#		netlist. Changes to Fitter assignments, however, do not cause
	#		the design partition to be recompiled.
	#
	#	EMPTY
	#		Directs the Compiler to compile the design partition using an
	#		empty placeholder netlist. Virtual pins are used at the design
	#		partition boundaries to preserve the interface of the design
	#		partition.
	#	
	# PARTITION_FITTER_PRESERVATION_LEVEL
	#
	#	This assignment can be used to set the fitter preservation
	#	level of a partition. The assignment can take on one of the
	#	following values:
	#	
	#	NETLIST_ONLY
	#		Directs the Compiler to preserve only the netlist atoms of
	#		the design partition and to re-place and re-route the design
	#		partition.
	#	
	#	PLACEMENT
	#		Directs the Compiler to preserve the netlist atoms and their
	#		placement in the design partition, and to re-route the design
	#		partition.
	#	
	#	PLACEMENT_AND_ROUTING
	#		Directs the Compiler to preserve the netlist atoms and their
	#		placement and routing in the design partition, minimizing
	#		compilation time.
	#
	#	PLACEMENT_AND_ROUTING_AND_TILE
	#		Directs the Compiler to preserve the netlist atoms and their
	#		placement, routing and tile in the design partition, minimizing
	#		compilation time.
	#
	###############################################################

	set_global_assignment -name INCREMENTAL_COMPILATION FULL_INCREMENTAL_COMPILATION

	set_instance_assignment -name PARTITION_HIERARCHY no_file_for_top_partition -to | -section_id Top
	set_global_assignment -name PARTITION_NETLIST_TYPE SOURCE -section_id Top

	set_instance_assignment -name PARTITION_HIERARCHY video_87b9c99ecc36aea68297ac249764921 -to "Video:Video0" -section_id "Video:Video0"
	set_global_assignment -name PARTITION_NETLIST_TYPE POST_SYNTH -section_id "Video:Video0"

	# Commit assignments
	export_assignments

	# Close project
	if {$need_to_close_project} {
		project_close
	}
}
