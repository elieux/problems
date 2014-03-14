<?php

echo iconv('KOI8-R', 'UTF-8', chr(0xd1) . chr(0xe5) . chr(0xf2) . chr(0xf3) . chr(0xed) . chr(0xfc));
echo PHP_EOL;
