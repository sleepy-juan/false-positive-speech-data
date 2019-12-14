var filename =1;
var yesno = ["Comprehended"];
var answers = ["Answers"];
const totalQuestions = 8;

document.getElementById("submit").addEventListener("click", function(){
    if(recordCurrent()){
        loadNext();
        console.log(yesno);
        console.log(answers);
    }
    if(filename==totalQuestions+1){
        exportCSV();
    }
})

function loadNext(){
    var music = document.getElementById('voice');
    music.pause();
    var directory = "voice/"+filename+".wav";
    music.src= directory;
    music.load();
    filename+=1;
    var qnum = document.getElementById("questionNumber");
    qnum.innerHTML = filename;
}

function recordCurrent(){
    var radios = document.getElementsByName('comprehend');
    if(!radios[0].checked && !radios[1].checked){
        return false;
    }

    var text = document.getElementById("content");
    if(!text.value){
        return false;
    }
    else{
        answers.push(text.value);
        text.value = "";
    }

    if(radios[0].checked){
        yesno.push(true);
        radios[0].checked = false;
    }
    if(radios[1].checked){
        yesno.push(false);
        radios[0].checked = false;
    }
    return true;
    
}

function exportCSV(){
    const rows = [
        yesno,
        answers
    ]
    let csvContent = "data:text/csv;charset=utf-8,";

    rows.forEach(function(rowArray) {
        let row = rowArray.join(",");
        csvContent += row + "\r\n";
    });

    var encodedUri = encodeURI(csvContent);
    var link = document.createElement("a");
    link.setAttribute("href", encodedUri);
    link.setAttribute("download", "my_data.csv");
    document.body.appendChild(link);
    link.click();

    window.alert("Your Test is Complete. Submit the downloaded CSV file to the researchers")
}