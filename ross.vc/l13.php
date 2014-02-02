<?php

$text = 'vigenere';
$key = 'cipher';
$addtext = '';
$subtext = '';

for ($i = 0; $i < strlen($text); $i++)
{
	$addtext .= chr(ord($text[$i]) + ord($key[$i % strlen($key)]) - ord('a'));
	$subtext .= chr(ord($text[$i]) - ord($key[$i % strlen($key)]) + ord('a'));
}
echo $addtext . PHP_EOL;
echo $subtext . PHP_EOL;