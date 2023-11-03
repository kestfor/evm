#include <C:\libusb\libusb-1.0.26-binaries\libusb-MinGW-x64\include\libusb-1.0\libusb.h>
#include <stdio.h>
libusb_context* context = NULL;
static void find_dev(libusb_device **devs)
{
    libusb_device *dev;
    int i = 0, j = 0;
    while ((dev = devs[i++]) != NULL) {
        printf("\ndev/num %d\n", i);
        struct libusb_device_descriptor desc;
        libusb_device_handle* handle = NULL;
        int ret;
        unsigned char string[256];
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor");
            return;
        }

        ret = libusb_open(dev, &handle);
        if (ret == LIBUSB_ERROR_NOT_SUPPORTED) {
            printf("not supported\n");
        }
        if (ret == LIBUSB_ERROR_NOT_FOUND) {
            printf("not found\n");
        }
        if (LIBUSB_SUCCESS == ret) {
            printf("get %04x:%04x device string descriptor \n", desc.idVendor, desc.idProduct);
            printf("iProduct[%d]:\n", desc.iProduct);
            ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, string, sizeof(string));
            if (ret > 0) {
                printf("%s\n", string);
            } else {
                printf("not found\n");
            }
        }
    }
}
int main(void) {
    libusb_device **devs;
    int r;
    ssize_t cnt;
    r = libusb_init(&context);
    if (r < 0)
        return r;
    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0){
        libusb_exit(NULL);
        return (int) cnt;
    }
    find_dev(devs);
    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return 0;
}