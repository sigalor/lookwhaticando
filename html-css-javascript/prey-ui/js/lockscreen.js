var inputPasswordClicked = false;

function initializeLockscreen()
{
	$(window).bind("unload", function()
	{
		inputPasswordClicked = false;
		$("#loginPasswordInput").blur().val("");
	});
	
	$("#loginPasswordInput").mouseenter(function()
	{
		if(!inputPasswordClicked)
			$(this).attr("type", "text").css("background", "green").css("color", "white").val("\"FParad0x?\"");
	})
	.mouseout(function()
	{
		if(!inputPasswordClicked)
			$(this).attr("type", "password").css("background", "white").css("color", "").val("");
	})
	.click(function()
	{
		if(inputPasswordClicked)
			return;
		inputPasswordClicked = true;
		
		let setPassword = "FParad0x?";
		let passwordInputter = function()
		{
			if(setPassword.length == 0)
			{
				setTimeout(function() { slideToPage("overview"); }, 200);
				return;
			}
			$("#loginPasswordInput").val($("#loginPasswordInput").val() + setPassword.substr(0, 1));
			setPassword = setPassword.substr(1);
			setTimeout(passwordInputter, 100);
		};
		$(this).attr("type", "password").css("background", "white").css("color", "").val("");
		setTimeout(passwordInputter, 100);
	});
}
