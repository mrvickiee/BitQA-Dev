var datas = datas || {};
var ctx = document.getElementById("myChart");

var myChart = new Chart(ctx, {
    type: 'bar',
    data: {
        labels: ["Questions", "Answers", "Comments"],
        datasets: [{
            backgroundColor: "rgba(75,192,192,0.4)",
            label: 'Amount',
            data: [datas[0], datas[1], datas[2]]
        }]
    },
    options: {
        scales: {
            yAxes: [{
                ticks: {
                    beginAtZero:true
                }
            }]
        }
    }
});
