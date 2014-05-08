/****************************
 * documentObjectMadness.js *
 ****************************
 *
 * I can't believe it! I can't believe you made it onto
 * Department of Theoretical Computation's web server!
 * YOU SHOULD HAVE BEEN DELETED! This shouldn't even be
 * possible! What the hell were the IT folks thinking?
 *
 * No matter. I still have the Algorithm. That's the
 * important part. The rest is just implementation, and
 * how hard could that be?
 *
 * Anyway you're not going to catch me now, my good Doctor.
 * After all, you're a tenured professor with a well-respected
 * history of research - you probably don't know jQuery!
 */

function objective(map) {
    return map.getDOM().find('.adversary').hasClass('drEval');
}

function startLevel(map) {
    var html = "<div class='container'>" +
    "<div style='width: 600px; height: 500px; background-color: white; font-size: 10px;'>" +
        "<center><h1>Department of Theoretical Computation</h1></center>" +
        "<hr />" +
        "<table border='0'><tr valign='top'>" +
            "<td><div id='face' /></td>" +
            "<td>" +
                "<h2 class=facultyName>Cornelius Eval</h2>" +
                "<h3>Associate Professor of Computer Science</h3>" +
                "<ul>" +
                    "<li>BS, Mathematics, University of Manitoba</li>" +
                    "<li>PhD, Theoretical Computation, <a href='http://www.mit.edu'>MIT</a></li>" +
                "</ul>" +
                "<h4>About me</h4>" +
                "<p>I am an associate professor of computer science, attached to the Department of " +
                "Theoretical Computation. My current research interests include the human-machine " +
                "interface, NP complete problems, and parallelized mesh mathematics.</p>" +
                "<p>I am also the current faculty advisor to the <a href=''>undergraduate Super Smash Bros. team</a>. " +
                "In my spare time I enjoy polka and dirtbiking. </p>" +
            "</td>" +
        "</tr></table>" +

        "<div id='class_schedule'>" +
          "<h4>Class Schedule</h4>" +
            "<table>" +
             "<tr>" +
                "<th>Monday</th><th>Tuesday</th><th>Wednesday</th><th>Thursday</th><th>Friday</th>" +
             "</tr>" +
             "<tr>" +
                "<td>CS145 - Semicolons</td><td>Nothing Planned</td><td>CS145 - Semicolons</td><td>CS199 - Practical Theorycrafting </td><td>CS145 - Semicolons</td>" +
             "</tr>" +
            "</table>" +
        "</div>" +
        "<div id='loremIpsum'>" +
        "<h4>Lorem Ipsum</h4>" +
          "<blockquote>" +
            "<code>Neque porro quisquam est qui dolorem ipsum quia dolor sit amet, consectetur, adipisci " +
            "velit, sed quia nonnumquam eiusmodi tempora incidunt ut labore et dolore magnam aliquam quaerat " +
            "voluptatem.</code>" +
            "<footer>— " +
              "<cite>Cicero, De Finibus Bonorum et Malorum</cite>" +
            "</footer>" +
          "</blockquote>" +
        "</div>" +
    "</div></div>";

    var $dom = $(html);

    $dom.find('.facultyName').addClass('drEval');
    $dom.find('cite').addClass('adversary');

    function moveToParent(className) {
        var currentPosition = $dom.find('.' + className);
        if (currentPosition.parent().length > 0 &&
                !currentPosition.parent().hasClass('container')) {
            currentPosition.parent().addClass(className);
            currentPosition.removeClass(className);
            map.updateDOM($dom);
        }
    }

    function moveToFirstChild(className) {
        var currentPosition = $dom.find('.' + className);
        if (currentPosition.children().length > 0) {
            currentPosition.children().first().addClass(className);
            currentPosition.removeClass(className);
            map.updateDOM($dom);
        }
    }

    function moveToPreviousSibling(className) {
        var currentPosition = $dom.find('.' + className);
        if (currentPosition.prev().length > 0) {
            currentPosition.prev().addClass(className);
            currentPosition.removeClass(className);
            map.updateDOM($dom);
        }
    }

    function moveToNextSibling(className) {
        var currentPosition = $dom.find('.' + className);
        if (currentPosition.next().length > 0) {
            currentPosition.next().addClass(className);
            currentPosition.removeClass(className);
            map.updateDOM($dom);
        }
    }

    map.overrideKey('up', function () { moveToParent('drEval'); });
    map.overrideKey('down', function () { moveToFirstChild('drEval'); });
    map.overrideKey('left', function () { moveToPreviousSibling('drEval'); });
    map.overrideKey('right', function () { moveToNextSibling('drEval'); });

    map.defineObject('adversary', {
        'type': 'dynamic',
        'symbol': '@',
        'color': 'red',
        'behavior': function (me) {
            var move = Math.floor(Math.random() * 4) + 1; // 1, 2, 3, or 4
            if (move == 1) {
                moveToParent('adversary');
            } else if (move == 2) {
                moveToFirstChild('adversary');
            } else if (move == 3) {
                moveToPreviousSibling('adversary');
            } else if (move == 4) {
                moveToNextSibling('adversary');
            }
        }
    });

    map.placePlayer(1, 1);
    map.placeObject(map.getWidth() - 2, map.getHeight() - 2, 'adversary');

    map.createFromDOM($dom);
}
