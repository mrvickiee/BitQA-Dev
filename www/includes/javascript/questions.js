function checkLogin()
{
    if ((Cookies.get("username") == null) ||
        (Cookies.get("username") == undefined)
    ) {
        $("#genericModalBoday").html("<p>You must be logged in to vote, <a href=\"/login.html\">Login</a></p>");
        $("#genericModal").modal("show");
        return true;
    } else {
        return false;
    }
}

function checkSelf(currentButton)
{
    if (Cookies.get("username") == currentButton.attr("data-user-id")) {
        $("#genericModalBoday").html("<p>You can't vote your own content</p>");
        $("#genericModal").modal("show");
        return true;
    } else {
        return false;
    }
}

$(".vote-up").click(function(event) {

    var content = $(event.target);

    if (checkLogin()) {
        return false;
    };

    if (checkSelf(content)) {
        return false;
    };

    $("#genericAlert").fadeOut();

    var downVote = $("#down" + content.attr("data-content-id"));

    // Check vote down is not pressed
    if (downVote.attr("data-selected") == "true") {
        $("#genericErrorText").text("You Must Remove your down vote before you can upvote");
        $("#genericAlert").fadeIn();
        return;
    };

    if (content.attr("data-selected") == "true") {

        $(".loading").fadeIn();

        $.ajax({
            type: "post",
            url: "/api/vote.html",
            data: {
                contentId: content.attr("data-content-id"),
                userId: Cookies.get("username"),
                voteType: content.attr("data-vote-type"),
                voteAction: "unvote"
            },

            success: function (data)
            {
                if (data.hasOwnProperty("errorMessage")) {
                    $("#genericErrorText").text("Test "
                        + data.errorMessage
                        + ": " + data.errorDetail
                        );

                    $("#genericAlert").fadeIn();
                } else {

                    // Vote up current question
                    var score = $("#" + content.attr("data-content-id")).text();
                    var finalScore = parseInt(score) - 1;

                    $("#" + content.attr("data-content-id")).text(finalScore);

                    // User has selected
                    content.css("background-color", "white");
                    content.attr("data-selected", false);

                };
            },

            error: function (error)
            {
                console.log(error);
                $("#genericErrorText").text("Network Error");
                $("#genericAlert").fadeIn();
            },

            complete: function ()
            {
                $(".loading").fadeOut();
            }
        });

    } else {

        $(".loading").fadeIn();

        $.ajax({
            type: "post",
            url: "/api/vote.html",
            data: {
                contentId: content.attr("data-content-id"),
                userId: Cookies.get("username"),
                voteType: content.attr("data-vote-type"),
                voteAction: "vote"
            },

            success: function (data)
            {
                if (data.hasOwnProperty("errorMessage")) {
                    $("#genericErrorText").text("Test "
                        + data.errorMessage
                        + ": " + data.errorDetail
                        );

                    $("#genericAlert").fadeIn();
                } else {

                    // Vote up current question
                    var score = $("#" + content.attr("data-content-id")).text();
                    var finalScore = parseInt(score) + 1;

                    $("#" + content.attr("data-content-id")).text(finalScore);

                    // User has selected
                    content.css("background-color", "green");
                    content.attr("data-selected", true);

                };
            },

            error: function (error)
            {
                console.log(error);
                $("#genericErrorText").text("Network Error");
                $("#genericAlert").fadeIn();
            },

            complete: function ()
            {
                $(".loading").fadeOut();
            }
        });

    }

});

$(".vote-down").click(function(event) {

    var content = $(event.target);

    if (checkLogin()) {
        return false;
    };

    if (checkSelf(content)) {
        return false;
    };

    $("#genericAlert").fadeOut();

    var upVote = $("#up" + content.attr("data-content-id"));

    // Check vote down is not pressed
    if (upVote.attr("data-selected") == "true") {
        $("#genericErrorText").text("You Must Remove your up vote before you can down vote");
        $("#genericAlert").fadeIn();
        return;
    };

    var voteAct = "";

    if (content.attr("data-selected") == "true") {

        $(".loading").fadeIn();

        $.ajax({
            type: "post",
            url: "/api/vote.html",
            data: {
                contentId: content.attr("data-content-id"),
                userId: Cookies.get("username"),
                voteType: content.attr("data-vote-type"),
                voteAction: "unvote"
            },

            success: function (data)
            {
                if (data.hasOwnProperty("errorMessage")) {
                    $("#genericErrorText").text("Test "
                        + data.errorMessage
                        + ": " + data.errorDetail
                        );

                    $("#genericAlert").fadeIn();
                } else {

                    // Vote up current question
                    var score = $("#" + content.attr("data-content-id")).text();
                    var finalScore = parseInt(score) + 1;

                    $("#" + content.attr("data-content-id")).text(finalScore);

                    // User has selected
                    content.css("background-color", "white");
                    content.attr("data-selected", false);

                };
            },

            error: function (error)
            {
                console.log(error);
                $("#genericErrorText").text("Network Error");
                $("#genericAlert").fadeIn();
            },

            complete: function ()
            {
                $(".loading").fadeOut();
            }
        });

    } else {

        $(".loading").fadeIn();

        $.ajax({
            type: "post",
            url: "/api/vote.html",
            data: {
                contentId: content.attr("data-content-id"),
                userId: Cookies.get("username"),
                voteType: content.attr("data-vote-type"),
                voteAction: "vote"
            },

            success: function (data)
            {
                if (data.hasOwnProperty("errorMessage")) {
                    $("#genericErrorText").text("Test "
                        + data.errorMessage
                        + ": " + data.errorDetail
                        );

                    $("#genericAlert").fadeIn();
                } else {

                    // Vote up current question
                    var score = $("#" + content.attr("data-content-id")).text();
                    var finalScore = parseInt(score) - 1;

                    $("#" + content.attr("data-content-id")).text(finalScore);

                    // User has selected
                    content.css("background-color", "red");
                    content.attr("data-selected", true);

                };
            },

            error: function (error)
            {
                console.log(error);
                $("#genericErrorText").text("Network Error");
                $("#genericAlert").fadeIn();
            },

            complete: function ()
            {
                $(".loading").fadeOut();
            }
        });
    }

});
