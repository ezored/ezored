from files.core import const


def run(proj_path, params):
    return {
        "default": {
            "version": "1.0.0",
            "bucket_name": const.AWS_S3_DOCS_BUCKET_NAME,
            "bucket_path": "docs",
            "url": "https://{0}.s3.amazonaws.com/{1}".format(
                const.AWS_S3_DOCS_BUCKET_NAME,
                "docs",
            ),
            "append_version": False,
        },
    }
