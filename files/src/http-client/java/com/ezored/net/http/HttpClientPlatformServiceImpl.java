package com.ezored.net.http;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
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
        int responseCode = 0;
        StringBuilder responseBody = new StringBuilder();
        ArrayList<HttpHeader> responseHeaders = new ArrayList<>();

        try {
            // general
            URL url = new URL(request.getUrl());
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            StringBuilder body = new StringBuilder();

            connection.setRequestMethod(getMethodFromHttpMethod(request.getMethod()));

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

                        body.append(String.format(Locale.getDefault(), format, URLEncoder.encode(param.getName(), "UTF-8"), URLEncoder.encode(param.getValue(), "UTF-8")));
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

            // get response code
            try {
                responseCode = connection.getResponseCode();
            } catch (Exception e) {
                e.printStackTrace();
            }

            // get response headers
            try {
                responseHeaders = getResponseHeaders(connection);
            } catch (Exception e) {
                e.printStackTrace();
            }

            // get content
            try {
                InputStream is = connection.getInputStream();

                // check for gzip encoding
                String encoding = connection.getHeaderField("Content-Encoding");

                if (encoding != null && encoding.contains("gzip")) {
                    is = new GZIPInputStream(is);
                }

                // get response data
                BufferedReader br = new BufferedReader(new InputStreamReader(is));
                String line = "";

                while ((line = br.readLine()) != null) {
                    responseBody.append(line);
                }

                br.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return new HttpResponse(responseCode, responseBody.toString(), request.getUrl(), responseHeaders);
    }

    private String getMethodFromHttpMethod(HttpMethod httpMethod) {
        if (httpMethod == null) {
            return "";
        }

        switch (httpMethod) {
            case METHOD_GET:
                return "GET";
            case METHOD_POST:
                return "POST";
            case METHOD_PUT:
                return "PUT";
            case METHOD_HEAD:
                return "HEAD";
            case METHOD_PATCH:
                return "PATCH";
            case METHOD_TRACE:
                return "TRACE";
            case METHOD_DELETE:
                return "DELETE";
            case METHOD_CONNECT:
                return "CONNECT";
            case METHOD_OPTIONS:
                return "OPTIONS";
            default:
                return "";
        }
    }

    private ArrayList<HttpHeader> getResponseHeaders(HttpURLConnection connection) {
        ArrayList<HttpHeader> headers = new ArrayList<>();

        for (Map.Entry<String, List<String>> entries : connection.getHeaderFields().entrySet()) {
            String headerName = entries.getKey();
            StringBuilder headerValue = new StringBuilder();

            for (String value : entries.getValue()) {
                headerValue.append(value).append(",");
            }

            if (headerName != null) {
                HttpHeader header = new HttpHeader(headerName, headerValue.toString());
                headers.add(header);
            }
        }

        return headers;
    }

}
