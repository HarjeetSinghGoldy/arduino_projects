var fs = require('fs');
var XLSX = require('xlsx');
var workbook = XLSX.readFile('./file/1.xlsx');
var sheet_name_list = workbook.SheetNames;
console.log("===>csv",XLSX.utils.sheet_to_csv(workbook.Sheets[sheet_name_list[0]]))
console.log("===>json",XLSX.utils.sheet_to_json(workbook.Sheets[sheet_name_list[0]]))
console.log("===>html",XLSX.utils.sheet_to_html(workbook.Sheets[sheet_name_list[0]]))


fs.writeFile("./file/1.csv",XLSX.utils.sheet_to_csv(workbook.Sheets[sheet_name_list[0]]), function(err) {
    if(err) {
        return console.log(err);
    }
    console.log("The csv file was saved!");
});
fs.writeFile("./file/1.json",JSON.stringify(XLSX.utils.sheet_to_json(workbook.Sheets[sheet_name_list[0]])), function(err) {
    if(err) {
        return console.log(err);
    }
    console.log("The json file was saved!");
});
fs.writeFile("./file/1.html",XLSX.utils.sheet_to_html(workbook.Sheets[sheet_name_list[0]]), function(err) {
    if(err) {
        return console.log(err);
    }
    console.log("The html file was saved!");
});
