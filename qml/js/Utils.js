function isSun() {
    var myDate = new Date();
    var hour = myDate.getHours();
    if (hour >=6 && hour <= 19) {
        return 1;
    }
    return 0;
}


function getWeatherIconName(type) {
    var day = isSun();
    var file;
    
    console.log("======== type is " + type);
    
    if(type === "0" ||  type === "18") {
        file = day? "w1_s" : "wi_m";
    }else if (type === "2") {
        file = "w3";
    }else if (type === "3"||type === "7"||type === "21") {
        file = "w4";
    }else if (type === "4") {
        file = "w9";
    }else if (type === "8"||type === "9"||type === "22"||type === "23") {
        file = "w5_6";
    }else if (type === "10"||type === "11"||type === "24") {
        file = "w7";
    }else if (type === "12"||type === "25") {
        file = "w8";
    }else if (type === "5"||type === "6"||type === "19") {
        file = "w10";
    }else if (type === "14") {
        file = "w11_12";
    }else if (type === "15"||type === "26") {
        file = "w13_14";
    }else if (type === "16"||type === "27") {
        file = "w15";
    }else if (type === "17"||type === "28") {
        file = "w16";
    }else if (type === "20"||type === "29"||type === "30"||type === "31") {
        file = "w17";
    }else if (type === "19"||type === "53") {
        file = "w30";
    }else {
        file = day ? "w2_s" : "w2_m";
    }
    return file + ".png";
}
