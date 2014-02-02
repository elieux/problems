<?php

if ($argc !== 4)
	die("Usage: {$argv[0]} infile outfile1 outfile2");

$in = $argv[1];
$outleft = $argv[2];
$outright = $argv[3];

echo "{$in}\t{$outleft}\t{$outright}\n";

$in = file($in, FILE_IGNORE_NEW_LINES);
$outleft = file($outleft, FILE_IGNORE_NEW_LINES);
$outright = file($outright, FILE_IGNORE_NEW_LINES);

foreach ($in as $i => $inline)
{
	if (trim($outleft[$i]) !== trim($outright[$i]))
		echo "{$inline}\t{$outleft[$i]}\t{$outright[$i]}\n";
}
