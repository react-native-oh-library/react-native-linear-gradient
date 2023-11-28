import { Platform } from "react-native";
import LinearGradientIos from "./index.ios.js";
import LinearGradientAndroid from "./index.android.js";
import LinearGradientWindows from "./index.windows.js";
import LinearGradientHarmony from "./index.harmony.js";

export const LinearGradient = Platform.OS === "ios"
  ? LinearGradientIos : Platform.OS === "android"
  ? LinearGradientAndroid : Platform.OS === "harmony"
  ? LinearGradientHarmony : LinearGradientWindows;

export default LinearGradient;
