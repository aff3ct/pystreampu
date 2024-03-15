import aff3ct._ext
from aff3ct._ext import int16


def sink(max_data_size: int,
           dtype: aff3ct._ext.dtype = int16):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f'Sink_{str(dtype)}'
    class_type = getattr(aff3ct._ext.snk, class_name)
    return class_type(max_data_size)


def sink_no(max_data_size: int,
            dtype: aff3ct._ext.dtype = int16):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f'Sink_NO_{str(dtype)}'
    class_type = getattr(aff3ct._ext.src, class_name)
    return class_type(max_data_size)


def sink_user_binary(max_data_size: int,
                       filename: str,
                       dtype: aff3ct._ext.dtype = int16):
    if not isinstance(dtype, aff3ct._ext.dtype):
        msg = f"type '{type(dtype)}' does not name an AFF3CT datatype."
        raise TypeError(msg)
    class_name = f'Sink_user_binary_{str(dtype)}'
    class_type = getattr(aff3ct._ext.src, class_name)
    return class_type(max_data_size, filename)



__all__ = ['sink', 'sink_user_binary', 'sink_no']