<?php

dl('php_gd2');

$img = imagecreatefrompng('l16.png');
list($w, $h) = getimagesize('l16.png');

// function rgb($color) {
	// return array($color & 0xff0000 >> 2 * 8, $color & 0x00ff00 >> 8, $color & 0x0000ff);
// }

// for ($x = 0; $x < $w; $x++)
	// for ($y = 0; $y < $h; $y++)
	// {
		// $color = imagecolorat($img, $x, $y);
		// $colors = imagecolorsforindex($img, $color);
		// if ($colors['alpha'] != 0)
			// echo "{$colors['alpha']}\n";
		// list($r, $g, $b) = rgb($color);
		// // echo "{$r} {$g} {$b}\n";
		// if ($r != $g || $r != $b)
			// imagesetpixel($img, $x, $y, 0x000000);
		// else
			// imagesetpixel($img, $x, $y, 0xffffff);
	// }


// FUCK YOU, gd2

$img = imagecreatetruecolor($w, $h);

$pixels = substr(file_get_contents('l16.pat'), 32);

for ($x = 0; $x < $w; $x++)
	for ($y = 0; $y < $h; $y++)
	{
		// $r = ord(substr($pixels, $w * $y + $x + 0, 1));
		// $g = ord(substr($pixels, $w * $y + $x + 1, 1));
		// $b = ord(substr($pixels, $w * $y + $x + 2, 1));
		// $pixel = $h * $x + $y;
		$pixel = $w * $y + $x;
		$r = ord(substr($pixels, 3 * $pixel + 0, 1));
		$g = ord(substr($pixels, 3 * $pixel + 1, 1));
		$b = ord(substr($pixels, 3 * $pixel + 2, 1));
		echo "{$r} {$g} {$b}\n";
		if ($r != $g || $r != $b)
			imagesetpixel($img, $x, $y, 0x000000);
		else
			imagesetpixel($img, $x, $y, 0xffffff);
	}

imagepng($img, 'l16.php.png');
