<?php

$descriptorspec = array(
	0 => array('pipe', 'rb'),
	// 0 => array('file', 'tester.input.txt', 'r'),
	1 => array('pipe', 'wb'),
	// 1 => array('file', 'tester.output.txt', 'wb'),
	2 => array('pipe', 'ab'),
);
$iMin = 999999;
$iMax = 1000000;

$jMin = 999999;
$jMax = 1000000;

$proc = proc_open('solution.exe', $descriptorspec, $pipes);
if (!is_resource($proc))
{
	echo "error opening process";
	exit;
}

register_shutdown_function('array_map', 'fclose', $pipes);
register_shutdown_function('proc_close', $proc);

foreach ($pipes as $v)
	stream_set_read_buffer($v, 0);

$max = ($iMax - $iMin + 1) * ($jMax - $jMin + 1);
$input = $pipes[0];
// $input = fopen('tester.input.txt', 'wb');
fwrite($input, "{$max}\n");

for ($i = $iMin; $i <= $iMax; $i++)
	for ($j = $jMin; $j <= $jMax; $j++)
	{
		$len = max(strlen((string)$i), strlen((string)$j));
		$sum = (string)($i + $j);
		if (strlen($sum) > $len)
			continue;
		$sum = str_pad($sum, $len, '0', STR_PAD_LEFT);
		fwrite($input, "\n{$len}\n");
		$iString = str_pad("{$i}", $len, '0', STR_PAD_LEFT);
		$jString = str_pad("{$j}", $len, '0', STR_PAD_LEFT);
		for ($k = 0; $len > $k; $k++)
			fwrite($input, "{$iString[$k]} {$jString[$k]}\n");
		fflush($input);
		$result = '';
		// $result = fgets($pipes[1]);
		// while (!feof($pipes[1]))
			$result .= fread($pipes[1], 1024);
		// $result = stream_get_contents($pipes[1]);
		$result = trim($result);
		if ("{$sum}" !== $result)
			echo "error: {$result} !== {$sum} = {$iString} + {$jString}\n";
	}
