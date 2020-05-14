#!/usr/bin/python3.7
import os
import argparse
import sys

parser = argparse.ArgumentParser(description='Generate State Diagrams')

parser.add_argument( '--root', required=True, help='The directory to search for statemachines' )
parser.add_argument( '--output', required=True, help='The directory to store generated files' )

args = parser.parse_args()

print( "Build StateMachine-Diagrams" )

files = {}
# Search for StateMachines
for dirpath, dirnames, filenames in os.walk( args.root ):
	for filename in [ f for f in filenames if ("StateMachine" in f) and f.endswith(".cpp") ]:
		files[ filename ] = ( os.path.join( dirpath, filename ))

for key, fsmfile in files.items():
	transits = []

	print( "Evaluate " + key )
	print( fsmfile )

	with open( fsmfile ) as f:
		for line in f:
			line = line.rstrip()
			if "Transit" in line:
				substring = line[ line.find("{")+1 : line.find("}") ]
				transits.append( substring )

	docfile = args.output + key.replace(".cpp",".md")
	with open( docfile, "w+" ) as f:
		wrapper = """
				@dot
					digraph D
					{{
						graph [ fontsize=12 ];
						node [ fontcolor=black, fontsize=10, margin=0.1];
						edge [ fontcolor=black, fontsize=10];
						label="[Generated from {}]";

						{}
					}}
				@enddot
		  	""".format( filename, "\n".join( transits ) )

		f.write( wrapper )


