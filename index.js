import { Platform } from "react-native";
import LinearGradientIos from "react-native-linear-gradient/index.ios.js";
import LinearGradientAndroid from "react-native-linear-gradient/index.android.js";
import LinearGradientWindows from "react-native-linear-gradient/index.windows.js";
import LinearGradientHarmony from "./index.harmony.js";

export const LinearGradient = Platform.OS === "ios"
  ? LinearGradientIos : Platform.OS === "android"
  ? LinearGradientAndroid : Platform.OS === "harmony"
  ? LinearGradientHarmony : LinearGradientWindows;

export default LinearGradient;
