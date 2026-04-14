/*
 * gettemperature("/sys/class/hwmon/hwmon0/device", "temp1_input");
 */

char *
gettemperature(char *base, char *sensor)
{
	char *co;

	co = readfile(base, sensor);
	if (co == NULL)
		return smprintf("");
	char *ret = smprintf("%02.0f°C", atof(co) / 1000);
	free(co);
	return ret;
}

