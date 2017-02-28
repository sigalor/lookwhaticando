function locationFromPageName(name)
{
	return "content/" + name + ".html";
}

function loadPage(name, callback, target)
{
	$(window).bind("unload", function() {});
	$(target===undefined ? "#currentPage" : target).load(locationFromPageName(name), callback);
}

function slideToPage(name)
{
	$("#nextPage").load(locationFromPageName(name), function()
	{
		$(".statusbarTime").html(new Date().timeNow());
		$("#currentPage").css("top", "110%");
		setTimeout(function() { window.location = name + ".html"; }, 1000);
	});
}
