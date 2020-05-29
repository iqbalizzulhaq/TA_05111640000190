<!DOCTYPE html>
<html lang="en">
<body>
<div class="col-lg-6">
    <div class="au-card m-b-30">
        <div class="au-card-inner">
            <h3 class="title-2 m-b-40">averangePingtime</h3>
            <div id="averangePingtime"></div>
           {{-- {{ dd(json_encode($averagePingtime))}} --}}
           {{-- {{ dd(json_encode($time))}} --}}
        </div>
    </div>
</div>

<script src="https://code.highcharts.com/highcharts.js"></script>
<script>    
Highcharts.chart('averangePingtime', {
    chart: {
        type: 'line'
    },
    title: {
        text: 'Monthly Average Temperature'
    },
    subtitle: {
        text: 'Source: WorldClimate.com'
    },
    xAxis: {
        categories: {!!json_encode($time)!!}
    },
    yAxis: {
        title: {
            text: 'Temperature (°C)'
        }
    },
    plotOptions: {
        line: {
            dataLabels: {
                enabled: true
            },
            enableMouseTracking: false
        }
    },
    series: [{
        name: 'Tokyo',
        data: {!!json_encode($averagePingtime)!!}
    
    }]
});
</script>

    {{-- <script>
        Highcharts.chart('averangePingtime', {
    chart: {
        type: 'area'
    },
    title: {
        text: 'Historic and Estimated Worldwide Population Growth by Region'
    },
    subtitle: {
        text: 'Source: Wikipedia.org'
    },
    xAxis: {
        categories: {!!json_encode($time)!!},
        tickmarkPlacement: 'on',
        title: {
            enabled: false
        }
    },
    yAxis: {
        title: {
            text: 'speed'
        },
        labels: {
            formatter: function () {
                return this.value;
            }
        }
    },
    tooltip: {
        split: true,
        valueSuffix: ' bytes/ms'
    },
    plotOptions: {
        area: {
            stacking: 'normal',
            lineColor: '#666666',
            lineWidth: 1,
            marker: {
                lineWidth: 1,
                lineColor: '#666666'
            }
        }
    },
    series: [{
        name: 'AverageTime',
        data: {!!json_encode($averagePingtime)!!}
    }]
});
    </script> --}}
</body>