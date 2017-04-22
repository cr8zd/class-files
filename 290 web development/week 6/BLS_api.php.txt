        $url = 'http://api.bls.gov/publicAPI/v1/timeseries/data/';
        $method = 'POST';
        $query = array(
                'seriesid'  => array('LEU0254555900', 'APU0000701111'),
                'startyear' => '2002',
                'endyear'   => '2012'
        );
        $pd = json_encode($query);
        $contentType = 'Content-Type: application/json';
        $contentLength = 'Content-Length: ' . strlen($pd);

        $result = file_get_contents(
                $url, null, stream_context_create(
                        array(
                                'http' => array(
                                        'method' => $method,
                                        'header' => $contentType . "\r\n" . $contentLength . "\r\n",
                                        'content' => $pd
                                ),
                        )
                )
        );

        var_dump($http_response_header);
        var_dump($result);