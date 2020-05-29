<?php

namespace App\Http\Controllers;

use Carbon\Traits\Timestamp;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\DB;

class DataController extends Controller
{
    public function show()
    {
    	// mengambil data dari table logs
    	$logs = DB::table('logs')->paginate(10);
		//dd($logs);
    	// mengirim data pegawai ke view index
    	return view('table',['logs' => $logs]);
 
	}
	
	
}
