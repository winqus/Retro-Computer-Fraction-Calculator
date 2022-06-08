const validKeys = String.raw` \`~1234567890-=!@#$%^&*()_+[]{}\|;:'",<.>/?`.split("");
const fracRe = /(-?|\+?)(-?|\+?)(\d+)(\/(-?|\+?)(\d+))?/g;
const fracPartsRe = /(-?\d+|\+?\d+)/g;
var allowInput = true;
var lastInput = "";
var lastFrac = {"numerator":0,"denominator":1,"sign":1}


/**
 * Makes a span element with a stylized fraction.
 * @param  {String} sign
 * @param  {String} numerator
 * @param  {String} denominator
 * @param  {Boolean} includeSign Show fraction sign (+ / -)?
 * @param  {Boolean} fullFraction Display full fraction (e.x.: 2 as 2/1)?
 * @return {String}      A span element. 
 */
function MakeFractionElement(sign, numerator, denominator, includeSign=true, fullFraction=false) {
    numerator = String(numerator);
    denominator = String(denominator);
    if(sign != "+" && sign != "-") {
        let re = /^-|^\+/g;
        if(re.test(numerator[0])) {
            sign = numerator[0];
            numerator = numerator.replace(re, "");
        }
        else if(re.test(denominator[0])) {
            sign = denominator[0];
            denominator = denominator.replace(re, "");
        }
        else if(includeSign) sign = "+";
    }
    if(includeSign == false && sign != "-")
        sign = "";
    let frac = "";
    if(numerator == "0" && !fullFraction) {
        return `<span>0</span>`
    }
    else if(denominator != "1" || fullFraction) {
        frac = `<span>${sign}</span><span><div class="frac">
                        <span>${numerator}</span>
                        <span class="symbol">/</span>
                        <span class="bottom">${denominator}</span> 
                    </div></span>`;
    } else {
        frac = `<span>${sign}</span><span>${numerator}</span>`;
    }
    return frac;
}

/**
 * Add a line to the terminal.
 * @param  {String} areatext The text (html element) to display
 * @param  {String} lineClass class to add (e.x.: "answer" or "created")
 * @param  {Boolean} scrollToEnd Scroll to terminal end after adding the line?
 * @return {void}
 */
function AddLine(areatext, lineClass="created", scrollToEnd=true) {
    let newline = `<div id="line" class="${lineClass} border">
            <span>${areatext}</span>
        </div>`;
    $("#line.cursor").before(newline);
    $("#inputarea").text("");
    if(scrollToEnd)
        $(".terminal").scrollTop( $(".terminal").prop("scrollHeight") );
}

/**
 * Tries to parse given text to fractions and send a request to the API.
 * @param  {String} areatext The text to parse
 * @return {void}
 */
function ParseAndSum(areatext) {
    let originalCopy = areatext;
    areatext = areatext.replace(/\s/g, "");

    var re = fracRe;
    let matches = areatext.match(re);
    let totalLength = 0;
    let parsedText = "";
    let postObj = {"fractions":[]}
    let includeSign = false;
    if(matches !== null)
        matches.forEach((match) => {
            let fracObj = {};
            totalLength += match.length;
            let sign = ((match[0] == "-" || match[0] == "+") && (match[1] == "-" || match[1] == "+")) ? match[0] : "";
            fracParts = match.match(fracPartsRe);
            let numerator = parseInt(fracParts[0]);
            numerator = isNaN(numerator) ? 0 : numerator;
            let denominator = parseInt(fracParts[1]);
            denominator = isNaN(denominator) ? 1 : denominator;
            fracObj['numerator'] = numerator;
            fracObj['denominator'] = denominator;
            fracObj['sign'] = sign == "-" ? -1 : 1;
            postObj['fractions'].push(fracObj);
            parsedText += MakeFractionElement(sign, numerator, denominator, includeSign, false);
            includeSign = true;
    });
    console.debug(postObj);
    if(totalLength != areatext.length || postObj['fractions'].length == 0 || postObj['fractions'].length != matches.length) {
        AddLine(originalCopy,"created");
        AddLine("Incorrect input. Try 'help'","answer");
        return;
    }
    AddLine(parsedText,"created");
    allowInput = false;
    $("#line.cursor").addClass("wait");
    $.ajax({
        type: "POST",
        url: "api/sum",
        data: JSON.stringify(postObj),
        contentType: "application/json; charset=utf-8",
        dataType: "json",
        success: (data)=>{
            console.debug(data);
            let sign = data['sign'] == -1 ? "-" : "+";
            AddLine(MakeFractionElement(sign, data['numerator'], data['denominator'], false, false), "answer");
            lastFrac = data;
            allowInput = true;
            $("#line.cursor").removeClass("wait").addClass("enter");
            
        },
        error: function(errMsg) {
            console.debug(errMsg.status);
            if(errMsg.status == 422)
                AddLine("Error. Incorrect arguments. (probably too large)","answer");
            else if(errMsg.status >= 500)
                AddLine(`Error ${errMsg.status}..`,"answer");
            else
                AddLine("Error...","answer");
                $("#line.cursor").removeClass("wait").addClass("enter");
            allowInput = true;
        }
    });

}

/**
 * Clears the terminal screen.
 * @return {void}
 */
function ClearScreen() {
    $( "#line.created" ).remove(); 
    $( "#line.answer" ).remove();
    $("#inputarea").text(""); 
}

/**
 * Displays usable commands and input examples in the terminal.
 * @return {void}
 */
function HelpScreen() {
    AddLine("help - commands and fraction input examples","created",true);
    `
    ╔═════════════╦══════════════════════════════════════╗
    ║ command     ║ explanation                          ║
    ╠═════════════╬══════════════════════════════════════╣
    ║ help        ║ -lists the commands                  ║
    ║ ans | frac  ║ -replaces 'ans' or 'frac' with       ║
    ║             ║  result fraction                     ║
    ║ dec         ║ -prints decimal value of the result  ║
    ║ cls         ║ -clears the screen                   ║
    ╚═════════════╩══════════════════════════════════════╝
    ╔════════════════════╗
    ║ input examples     ║
    ╠════════════════════╣
    ║ 4/8                ║
    ╠════════════════════╣
    ║ 1/2 + 5/6          ║
    ╠════════════════════╣
    ║ -1/3 + 5/-6 - 1/2  ║
    ╠════════════════════╣
    ║ 1/4 - -1/-6        ║
    ╚════════════════════╝
    `.replaceAll(/\n\s{4}/gm,"\n").split('\n').forEach((helpline) => {
        AddLine("<pre style='font-size: calc(var(--screen-font-size) * 0.65);'>"+helpline+"</pre>","answer",false);
    });
}


$(document).ready(function(){
    $("input").focus();
    $("#screen").click(() => {
        $("input").focus();
    });
    $("body").on("keydown", function(event){
        if(!allowInput)
            return;
        console.debug(`Event code is ${event.code}, ${event.key}, ${event.keyCode}`);
        if(validKeys.includes(event.key) || (event.keyCode >= 49 && event.keyCode <= 90)) {
            let areatext = $("#inputarea").text();
            $("#inputarea").text(areatext + event.key);
        }
        else if(event.code == "Backspace") {
            let areatext = $("#inputarea").text();
            $("#inputarea").text(areatext.replace(/.$/g,""));
        }
        else if(event.code == "Enter") {
            let areatext = $("#inputarea").text();
            areatext = areatext.toLowerCase();
            if(areatext == "cls") {
                ClearScreen();
            }
            else if(areatext == "frac" || areatext == "ans") {
                lastInput = areatext;
                let sign = lastFrac['sign'] == -1 ? "-" : "+";
                AddLine(MakeFractionElement(sign, lastFrac['numerator'], lastFrac['denominator'], false, false), "answer");
            }
            else if(areatext == "dec") {
                lastInput = areatext;
                AddLine("DEC "+lastFrac["sign"]*lastFrac["numerator"]/lastFrac["denominator"], "answer");
            }
            else if(areatext == "help") {
                lastInput = areatext;
                HelpScreen();
            }
            else {
                lastInput = areatext;
                let lastFracString = `${(lastFrac['sign'] == -1 ? "-":"+")}${lastFrac['numerator']}/${lastFrac['denominator']}`;
                areatext=areatext.replaceAll("frac",lastFracString).replaceAll("ans",lastFracString);
                ParseAndSum(areatext);
            }
        }
        else if(event.code == "ArrowUp") {
            $("#inputarea").text(lastInput);    
        }
        /*  
        if(event.code === 'Space') {
            let txt = $(this).val();
            txt = txt.replace(/\s+/g,"").replace(/\/+/g,"-")
            $(this).val(txt);
            // let cl = $(this).clone(true, true);
            // cl.val("");
            // $('body').append(cl);
            // cl.focus();
        }
        */
    });
});