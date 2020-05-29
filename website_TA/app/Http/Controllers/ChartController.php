<?php

namespace App\Http\Controllers;


use Carbon\Traits\Timestamp;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;


class ChartController extends Controller
{
    public function grafik()
    {
        $waktu = DB::table('logs')->pluck('timestamp');
        $time=[];

        $data = DB::table('logs')->pluck('averagePingtime');
        $averagePingtime=[];

        $data2 = DB::table('logs')->pluck('maxPingtime');
        $maxPingtime=[];

        $data3 = DB::table('logs')->pluck('minPingtime');
        $minPingtime=[];

        $data4 = DB::table('logs')->pluck('throughput');
        $throughput=[];

        foreach($data as $ap){
            $averagePingtime[]=$ap;
        }
        foreach($waktu as $wk){
            $time[]=$wk;
        }

        foreach($data2 as $mp){
            $maxPingtime[]=$mp;
        }
        foreach($data3 as $mip){
            $minPingtime[]=$mip;
        }
        foreach($data4 as $tr){
            $throughput[]=$tr;
        }


        //dd($minPingtime);
        //dd($throughput);
        return view('chart',['time' => $time,'averagePingtime'=>$averagePingtime,'maxPingtime'=>
        $maxPingtime,'minPingtime'=>$minPingtime,'throughput'=>$throughput]);
        
 
    }
    
    // public function data()
    // {
    //     $data = DB::table('logs')->pluck('averagePingtime');
    //     $averagePingtime=[];
    //     foreach($data as $ap){
    //         $averagePingtime[]=$ap;
    //     }
    //     //dd($averagePingtime);
    // 	return view('coba',['averagePingtime' => $averagePingtime]);
 
	// }
	
}
