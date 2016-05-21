$("#navBarLogout").click(function () {
	Cookies.remove("username");
	Cookies.remove("displayname");

	window.location = "/index.html";
})
