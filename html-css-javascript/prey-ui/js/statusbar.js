Date.prototype.timeNow = function()
{
	let retStr = "";
	retStr += ((this.getHours() < 10)?"0":"") + this.getHours();
	retStr += ":" + ((this.getMinutes() < 10)?"0":"") + this.getMinutes();
	return retStr;
}

function updateStatusbarTime()
{
	$(".statusbarTime").html(new Date().timeNow());
	setTimeout(updateStatusbarTime, 10000);
}
