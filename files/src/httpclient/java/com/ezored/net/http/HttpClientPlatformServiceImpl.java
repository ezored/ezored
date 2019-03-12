package com.ezored.net.http;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.zip.GZIPInputStream;

/**
 * Platform-Specific implementation of Http Client class
 */
public class HttpClientPlatformServiceImpl extends HttpClientPlatformService {

    @Override
    public HttpResponse doRequest(HttpRequest request) {
        try {
            // general
            URL url = new URL(request.getUrl());
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            StringBuilder body = new StringBuilder();

            connection.setRequestMethod(request.getMethod().toString().toUpperCase());

            // parameters
            if (request.getParams() != null && request.getParams().size() > 0) {
                for (HttpRequestParam param : request.getParams()) {
                    if (param.getName() != null && param.getValue() != null) {
                        String format;

                        if (body.length() > 0) {
                            format = "&%s=%s";
                        } else {
                            format = "%s=%s";
                        }

                        body.append(String.format(Locale.getDefault(), format, param.getName(), param.getValue()));
                    }
                }
            } else {
                body.append(request.getBody());
            }

            // request data
            if (body.length() > 0) {
                int contentLength = body.length();
                connection.setRequestProperty("Content-Length", Integer.toString(contentLength));
                connection.setRequestProperty("Charset", "UTF-8");

                // headers
                if (request.getHeaders() != null && request.getHeaders().size() > 0) {
                    for (HttpHeader header : request.getHeaders()) {
                        connection.setRequestProperty(header.getName(), header.getValue());
                    }
                }

                connection.setDoOutput(true);
                connection.setDoInput(true);
                connection.setUseCaches(false);
                connection.setInstanceFollowRedirects(true);
                connection.setReadTimeout(10000);
                connection.setConnectTimeout(15000);

                // connect to the server
                connection.connect();

                // write data to server
                OutputStream os = connection.getOutputStream();
                BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(os, "UTF-8"));
                writer.write(body.toString());
                writer.flush();
                writer.close();
                os.close();
            } else {
                // headers
                if (request.getHeaders() != null && request.getHeaders().size() > 0) {
                    for (HttpHeader header : request.getHeaders()) {
                        connection.setRequestProperty(header.getName(), header.getValue());
                    }
                }

                connection.setDoOutput(false);
                connection.setDoInput(true);
                connection.setUseCaches(false);
                connection.setInstanceFollowRedirects(true);
                connection.setReadTimeout(10000);
                connection.setConnectTimeout(15000);

                // connect to the server
                connection.connect();
            }

            // prepare and do the request
            InputStream is = connection.getInputStream();

            // check for gzip encoding
            String encoding = connection.getHeaderField("Content-Encoding");

            if (encoding != null && encoding.contains("gzip")) {
                is = new GZIPInputStream(is);
            }

            // get response data
            int responseCode = connection.getResponseCode();

            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            StringBuilder responseBody = new StringBuilder();
            String line = "";

            while ((line = br.readLine()) != null) {
                responseBody.append(line);
            }

            br.close();

            // get response headers
            ArrayList<HttpHeader> responseHeaders = getResponseHeaders(connection);

            return new HttpResponse(responseCode, responseBody.toString(), responseHeaders);
        } catch (Exception e) {
            e.printStackTrace();
            return new HttpResponse(0, "", new ArrayList<HttpHeader>());
        }
    }

    private ArrayList<HttpHeader> getResponseHeaders(HttpURLConnection connection) {
        ArrayList<HttpHeader> headers = new ArrayList<>();

        for (Map.Entry<String, List<String>> entries : connection.getHeaderFields().entrySet()) {
            String headerName = entries.getKey();
            String headerValue = "";

            for (String value : entries.getValue()) {
                headerValue += value + ",";
            }

            if (headerName != null && headerValue != null) {
                HttpHeader header = new HttpHeader(headerName, headerValue);
                headers.add(header);
            }
        }

        return headers;
    }

}
