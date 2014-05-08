/**********************
 * superDrEvalBros.js *
 **********************
 *
 * You're still here?! Well, Dr. Eval, let's see
 * how well you can operate with one less dimension.
 *
 * Give up now. Unless you have a magic mushroom
 * up your sleeve, it's all over.
 */

function startLevel(map) {
    var fl = Math.floor;
    var w = map.getWidth();
    var h = map.getHeight();

    map.placePlayer(1, fl(h/2)-1);
    var player = map.getPlayer();

    map.placeObject(w-1, fl(h/2)-1, 'exit');

    for (var x = 0; x < fl(w/2) - 5; x++) {
        for (var y = fl(h/2); y < h; y++) {
            map.placeObject(x, y, 'block');
        }
    }

    for (var x = fl(w/2) + 5; x <= w; x++) {
        for (var y = fl(h/2); y < h; y++) {
            map.placeObject(x, y, 'block');
        }
    }

    function gravity() {
        var x = player.getX();
        var y = player.getY() + 1;

        if (y === map.getHeight() - 2) {
            player.killedBy("gravity");
        }

        if (map.getObjectTypeAt(x,y) === "empty") {
            player.move("down");
        }

    }
    map.startTimer(gravity, 45);

    function jump() {

        map.startTimer(function () {
            player.move("up");
        }, 25);

    }

    player.setPhoneCallback(function () {
        var x = player.getX();
        var y = player.getY() + 1;

        if (map.getObjectTypeAt(x,y) !== "empty") {
            jump();
        }
    });
}

function validateLevel(map) {
    map.validateExactlyXManyObjects(1, 'exit');
    map.validateExactlyXManyObjects(520, 'block');
}
