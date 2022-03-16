import cv2
import math


class BlobDetector:
    def __init__(self, config={}, fid_size_px=620):
        if config:
            self.config = config.get("simpleBlobDetector", "")
            self.params = self.params_from_config(config)
            self.detector = cv2.SimpleBlobDetector_create(self.params)
        else:
            self.params = self.get_blob_detector_params(fid_size_px)
            self.detector = cv2.SimpleBlobDetector_create(self.params)

    @staticmethod
    def get_blob_detector_params(fid_size_px):
        params = cv2.SimpleBlobDetector_Params()
        # filter by area
        params.filterByArea = True
        params.minArea = int(0.9 * math.pi * (fid_size_px/2)**2)
        params.maxArea = int(1.1 * math.pi * (fid_size_px/2)**2)
        # filter by circularity
        params.filterByCircularity = False
        params.minCircularity = 0.1
        params.maxCircularity = 1.0
        # filter by convexity
        params.filterByConvexity = False
        params.minConvexity = 0.1
        params.maxConvexity = 1.0
        # filter by inertia
        params.filterByInertia = False
        params.minInertiaRatio = 0.1
        params.maxInertiaRatio = 1.0
        # filter by color
        params.filterByColor = False
        params.blobColor = 0

        return params

    def params_from_config(self, config):
        params = cv2.SimpleBlobDetector_Params()
        # filter by area
        if config["filterByArea"]["enabled"]:
            params.filterByArea = config["filterByArea"]["enabled"]
            if config["filterByArea"]["minArea"]:
                params.minArea = config["filterByArea"]["minArea"]
            if config["filterByArea"]["maxArea"]:
                params.maxArea = config["filterByArea"]["maxArea"]
        # filter by circularity
        if config["filterByCircularity"]["enabled"]:
            params.filterByCircularity = config["filterByCircularity"]["enabled"]
            if config["filterByCircularity"]["minCircularity"]:
                params.minCircularity = config["filterByCircularity"]["minCircularity"]
            if config["filterByCircularity"]["maxCircularity"]:
                params.maxCircularity = config["filterByCircularity"]["maxCircularity"]
        # filter by convexity
        if config["filterByConvexity"]["enabled"]:
            params.filterByConvexity = config["filterByConvexity"]["enabled"]
            if config["filterByConvexity"]["minConvexity"]:
                params.minConvexity = config["filterByConvexity"]["minConvexity"]
            if config["filterByConvexity"]["maxConvexity"]:
                params.maxConvexity = config["filterByConvexity"]["maxConvexity"]
        # filter by inertia
        if config["filterByInertia"]["enabled"]:
            params.filterByInertia = config["filterByInertia"]["enabled"]
            if config["filterByInertia"]["minInertiaRatio"]:
                params.minInertiaRatio = config["filterByInertia"]["minInertiaRatio"]
            if config["filterByInertia"]["maxInertiaRatio"]:
                params.maxInertiaRatio = config["filterByInertia"]["maxInertiaRatio"]
        if config["filterByColor"]["enabled"]:
            params.filterByColor = config["filterByColor"]["enabled"]
            if config["filterByColor"]["blobColor"]:
                params.blobColor = config["filterByColor"]["blobColor"]

        return params

    def detect(self, image):
        image = cv2.imread(image)
        keypoints = self.detector.detect(image)
        blobs = []
        for keypoint in keypoints:
            blobs.append({
                "center_x": keypoint.pt[0],
                "center_y": keypoint.pt[1],
                "size": keypoint.size
            })
        return blobs

