package com.ezored.io;

import android.content.Context;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.RandomAccessFile;
import java.net.URL;
import java.util.ArrayList;

public class FileHelperPlatformServiceImpl extends FileHelperPlatformService {

    private Context context;

    public Context getContext() {
        return context;
    }

    public void setContext(Context context) {
        this.context = context;
    }

    @Override
    public boolean createFile(String path) {
        File file = new File(path);

        try {
            return file.createNewFile();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return false;
    }

    @Override
    public boolean createFileWithStringContent(String path, String content) {
        File file = new File(path);
        FileOutputStream out = null;
        boolean success = false;

        try {
            out = new FileOutputStream(file);
            out.write(content.getBytes());
            out.flush();

            success = true;
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (out != null) {
                    out.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return success;
    }

    @Override
    public boolean createFileWithBinaryContent(String path, byte[] content) {
        File file = new File(path);
        FileOutputStream out = null;
        boolean success = false;

        try {
            out = new FileOutputStream(file);
            out.write(content);
            out.flush();

            success = true;
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (out != null) {
                    out.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return success;
    }

    @Override
    public boolean createDir(String path) {
        try {
            File directory = new File(path);
            return directory.mkdirs();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }

    @Override
    public ArrayList<String> listFiles(String path) {
        try {
            File directory = new File(path);
            File[] filesFound = directory.listFiles();
            ArrayList<String> files = new ArrayList<>();

            for (File fileFound : filesFound) {
                files.add(fileFound.getPath());
            }

            return files;
        } catch (Exception e) {
            e.printStackTrace();
        }

        return new ArrayList<>();
    }

    @Override
    public String getExtension(String path) {
        try {
            return path.substring(path.lastIndexOf("."));
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "";
    }

    @Override
    public String getFilename(String path) {
        try {
            File file = new File(path);
            return file.getName();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "";
    }

    @Override
    public String getBasename(String path) {
        try {
            String filename = getFilename(path);

            if (filename.indexOf(".") > 0) {
                return filename.substring(0, filename.lastIndexOf("."));
            } else {
                return filename;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "";
    }

    @Override
    public String getFilenameFromUrl(String url) {
        try {
            URL resource = new URL(url);
            String host = resource.getHost();

            if (host.length() > 0 && url.endsWith(host)) {
                return "";
            }

            int startIndex = url.lastIndexOf('/') + 1;
            int length = url.length();

            // find end index for ?
            int lastQMPos = url.lastIndexOf('?');
            if (lastQMPos == -1) {
                lastQMPos = length;
            }

            // find end index for #
            int lastHashPos = url.lastIndexOf('#');
            if (lastHashPos == -1) {
                lastHashPos = length;
            }

            // calculate the end index
            int endIndex = Math.min(lastQMPos, lastHashPos);
            return url.substring(startIndex, endIndex);
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "";
    }

    @Override
    public String getBasenameFromUrl(String url) {
        try {
            String filename = getFilenameFromUrl(url);

            if (filename.indexOf(".") > 0) {
                return filename.substring(0, filename.lastIndexOf("."));
            } else {
                return filename;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "";
    }

    @Override
    public boolean removeFile(String path) {
        try {
            File file = new File(path);
            return file.delete();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }

    @Override
    public boolean removeDir(String path) {
        try {
            File dir = new File(path);

            if (isDir(path)) {
                for (File child : dir.listFiles()) {
                    removeDir(child.getPath());
                }
            }

            return dir.delete();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }

    @Override
    public boolean isDir(String path) {
        try {
            File file = new File(path);
            return file.isDirectory();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }

    @Override
    public boolean isFile(String path) {
        try {
            File file = new File(path);
            return file.isFile();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }

    @Override
    public long getFileSize(String path) {
        try {
            File file = new File(path);
            return file.length();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return 0;
    }

    @Override
    public boolean copyFile(String from, String to) {
        InputStream in = null;
        OutputStream out = null;
        boolean success = false;

        try {
            in = new FileInputStream(from);
            out = new FileOutputStream(to);

            // transfer bytes from in to out
            byte[] buf = new byte[1024];
            int len;

            while ((len = in.read(buf)) > 0) {
                out.write(buf, 0, len);
            }

            success = true;
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (out != null) {
                    out.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }

            try {
                if (in != null) {
                    in.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return success;
    }

    @Override
    public boolean moveFile(String from, String to) {
        try {
            File fromFile = new File(from);
            File toFile = new File(to);

            return fromFile.renameTo(toFile);
        } catch (Exception e) {
            e.printStackTrace();
        }

        return false;
    }

    @Override
    public String join(String first, String second) {
        try {
            return new File(first, second).getPath();
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "";
    }

    @Override
    public String getFileContentAsString(String path) {
        RandomAccessFile f = null;
        byte[] data = new byte[0];

        try {
            f = new RandomAccessFile(new File(path), "r");

            // get and check length
            long longLength = f.length();
            int length = (int) longLength;

            if (length != longLength) {
                throw new IOException("File size >= 2 GB");
            }

            // read file and return data
            data = new byte[length];
            f.readFully(data);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (f != null) {
                    f.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return new String(data);
    }

    @Override
    public byte[] getFileContentAsBinary(String path) {
        RandomAccessFile f = null;
        byte[] data = new byte[0];

        try {
            f = new RandomAccessFile(new File(path), "r");

            // get and check length
            long longLength = f.length();
            int length = (int) longLength;

            if (length != longLength) {
                throw new IOException("File size >= 2 GB");
            }

            // read file and return data
            data = new byte[length];
            f.readFully(data);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (f != null) {
                    f.close();
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return data;
    }

    @Override
    public String getHomeDir() {
        if (context == null) {
            return "";
        }

        try {
            String basePath = context.getFilesDir().getAbsolutePath();

            if (basePath == null) {
                basePath = "";
            }

            return basePath;
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "";
    }

}
