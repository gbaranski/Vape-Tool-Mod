double getBatteryVoltage() {
    int raw = analogRead(34);
    return raw * 1.7 / 1000;
}

String formatBatteryVoltage(double batteryVoltage) {
    String batteryVoltageStr = String(batteryVoltage);
    return batteryVoltageStr.substring(0, batteryVoltageStr.length() - 1);

}
