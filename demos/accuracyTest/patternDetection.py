import cv2
import numpy as np
from demos.accuracyTest.utils.binaryBlobDetector import BinaryBlobDetector

MAGIC_NUMBER = 1.8645


class PatternDetector:
    def __init__(self, fid_size_px=620, num_fiducials=1):
        self.image, self.artificial_fiducial, self.padded = None, None, None
        self.num_fiducials = num_fiducials
        self.create_artificial_fid(fid_size_px, int(fid_size_px * MAGIC_NUMBER))

    def create_artificial_fid(self, inner_diam, outer_diam):
        self.inner_diam = inner_diam
        self.outer_diam = outer_diam
        pattern_sizeHW = [outer_diam, outer_diam]
        if outer_diam % 2 == 0:  # make sure pattern size is odd
            pattern_sizeHW[0] += 1
            pattern_sizeHW[1] += 1

        fiducial_pattern = np.zeros(pattern_sizeHW, dtype=np.uint8)
        cv2.circle(fiducial_pattern,
                   (pattern_sizeHW[1] // 2, pattern_sizeHW[0] // 2),
                   outer_diam // 2,
                   170,
                   cv2.FILLED)
        cv2.circle(fiducial_pattern,
                   (pattern_sizeHW[1] // 2, pattern_sizeHW[0] // 2),
                   inner_diam // 2,
                   220,
                   cv2.FILLED)
        self.artificial_fiducial = (fiducial_pattern.astype(np.float32) -
                                    fiducial_pattern.mean()) / fiducial_pattern.std()

    def detect(self, image):
        self.padded_match_img(image)
        return self.blob_detection()

    def padded_match_img(self, image):
        self.image = cv2.imread(image)
        self.greyscale = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        match_img = cv2.matchTemplate(self.greyscale.astype(np.float32),
                                      self.artificial_fiducial,
                                      cv2.TM_CCOEFF_NORMED)
        padded_match_8bits_img = np.zeros(
            (self.greyscale.shape[0], self.greyscale.shape[1]),
            dtype=np.uint8
        )
        padded_match_8bits_img[
            self.artificial_fiducial.shape[0] // 2: self.artificial_fiducial.shape[0] // 2 + match_img.shape[0],
            self.artificial_fiducial.shape[1] // 2: self.artificial_fiducial.shape[1] // 2 + match_img.shape[1]
        ] = (128 * (match_img + 1.0)).astype(np.uint8)
        self.padded = padded_match_8bits_img

    def blob_detection(self):
        blob_detector = BinaryBlobDetector()
        threshold = None
        bbox_list = None
        for threshold in range(255, 1, -1):
            _, threshold_img = cv2.threshold(self.padded, threshold, 255, cv2.THRESH_BINARY)
            bbox_list, _ = blob_detector.DetectBlobs(threshold_img)
            if len(bbox_list) >= self.num_fiducials:
                break
        return [{"center_x": blob[0][0],
                 "center_y": blob[0][1],
                 "size": self.inner_diam,
                 "threshold": threshold} for blob in bbox_list]
