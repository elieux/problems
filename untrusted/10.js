/*************
 * ambush.js *
 *************
 *
 * Oh. Oh, I see. This wasn't quite part of the plan.
 *
 * Looks like they won't let you take the Algorithm
 * without a fight. You'll need to carefully weave your
 * way through the guard drones.
 *
 * Well, time to improvise. Let's mess with their programming
 * a little, shall we?
 */

function startLevel(map) {
    function moveToward(obj, type) {
        var target = obj.findNearest(type);
        var leftDist = obj.getX() - target.x;
        var upDist = obj.getY() - target.y;

        var direction;
        if (upDist == 0 && leftDist == 0) {
            return;
        } if (upDist > 0 && upDist >= leftDist) {
            direction = 'up';
        } else if (upDist < 0 && upDist < leftDist) {
            direction = 'down';
        } else if (leftDist > 0 && leftDist >= upDist) {
            direction = 'left';
        } else {
            direction = 'right';
        }

        if (obj.canMove(direction)) {
            obj.move(direction);
        }
    }

    map.defineObject('attackDrone', {
        'type': 'dynamic',
        'symbol': 'd',
        'color': 'red',
        'onCollision': function (player) {
            player.killedBy('an attack drone');
        },
        'behavior': function (me) {

            if (me.getY() === 11) {
                return;
            }

            me.move(me.canMove('up') ? 'up' : 'left');

        }
    });

    map.defineObject('reinforcementDrone', {
        'type': 'dynamic',
        'symbol': 'd',
        'color': 'yellow',
        'onCollision': function (player) {
            player.killedBy('a reinforcement drone');
        },
        'behavior': function (me) {

        }
    });

    map.defineObject('defenseDrone', {
        'type': 'dynamic',
        'symbol': 'd',
        'color': 'green',
        'onCollision': function (player) {
            player.killedBy('a defense drone');
        },
        'behavior': function (me) {

            if (me.getY() === 11) {
                return;
            }

            me.move(me.canMove('up') ? 'up' : 'right');

        }
    });

    // just for decoration
    map.defineObject('water', {
        'symbol': '░',
        'color': '#44f'
    });

    map.placePlayer(0, 12);

    for (var x = 0; x < map.getWidth(); x++) {
        map.placeObject(x, 10, 'block');
        map.placeObject(x, 14, 'block');

        for (var y = 20; y < map.getHeight(); y++) {
            map.placeObject(x, y, 'water');
        }
    }

    map.placeObject(23, 11, 'attackDrone');
    map.placeObject(23, 12, 'attackDrone');
    map.placeObject(23, 13, 'attackDrone');

    map.placeObject(27, 11, 'defenseDrone');
    map.placeObject(27, 12, 'defenseDrone');
    map.placeObject(27, 13, 'defenseDrone');

    map.placeObject(24, 11, 'reinforcementDrone');
    map.placeObject(25, 11, 'reinforcementDrone');
    map.placeObject(26, 11, 'reinforcementDrone');
    map.placeObject(24, 13, 'reinforcementDrone');
    map.placeObject(25, 13, 'reinforcementDrone');
    map.placeObject(26, 13, 'reinforcementDrone');

    map.placeObject(map.getWidth()-1, 12, 'exit');
}

function validateLevel(map) {
    map.validateExactlyXManyObjects(1, 'exit');
}
