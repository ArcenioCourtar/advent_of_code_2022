# Run this script in the level above the output folder.
# Find all directories and subdirectories within the output/ dir.
# Split the results into separate argument with xargs.
# Run a shell command that reads whatever xargs put in "str",
# in said Shell command, find all files (VERY IMPORTANT SO YOU DON'T COUNT THE 4096 BYTES FOR EACH FOLDER),
# run du with the appropriate flags on all files located by find.
# tail -n 1 to only print out the final number which is the total n of bytes.
# Sort all the output in the final step.
# Calculations were all done by dumping the numbers into a calculator. :)
find output/* -type d | xargs -I str sh -c "echo str; find str -type f -print0 | du -scb --files0-from=- | tail -n 1" | sort -g