# File: xmlparser.pl
# Author: Adrianne Santinor
# Date: 12/8/17
# Description: Parses through a simple "Baby" XML file and identifies the line of a tag, whether it's opened or closed, and the name.
#								Also indicates whether or not there are any open tags at the end of the file.

$line = <STDIN>;
# keep track of current line
my $i = 1;

# make sure file is a baby xml file
if ($line =~ m/<\?xml version="1.0"\?>/){
	# "stack" to keep track of open tags
	@open = ();
	while ($line = <STDIN>){
		$i++;
		# searches file for an open tag
		if ($line =~ m/<(\w+_*\w*[^>]*)>/) {
			# place open tag found into beginning of array (i.e. top of stack)
			unshift(@open, $1);
			# loop to get indented statements
			for ($j = 1; $j < @open; $j++){
				print "  ";
			}
			print "$i: OPEN " . $1 . "\n";
		}
		# searches file for a close
		if ($line =~ m/<\/(\w+_*\w*[^>]*)>/) {
			$tag = $1;
			# check to see if close tag is equivalent to first element in array
			if ($open[0] !~ $tag){
				die "$i: close tag \"" . $tag . "\" doesn't match current open tag \"" . $open[0] . "\"\n";
			}
			# remove element at first array (i.e. pop it off the stack) 
			shift(@open);
			for ($j = 1; $j < @open+1; $j++){
				print "  ";
			}
			print "$i: CLOSE " . $tag . "\n";
		}
	}
	# if there are still unpopped tags in the array then they haven't been closed
	if (@open > 0){
		print "End of file with still-open tags: ";
		for ($j = 0; $j < @open; $j++) {
			print $open[$j] . ", ";
		}
		print "\n";
		die;
	}
}
else {
	die "Not a Baby-XML file";
}