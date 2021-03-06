<?php

/**
 * @file
 * Views hook implementations.
 */

use Drupal\field\FieldStorageConfigInterface;

/**
 * Implements hook_field_views_data().
 */
function geofield_field_views_data(FieldStorageConfigInterface $field_storage) {

  // TODO: This code only covers configurable fields, handle base table fields.
  // @see https://www.drupal.org/node/2489476.
  $data = views_field_default_views_data($field_storage);

  $field_name = $field_storage->getName();
  $field_label = NULL;

  foreach ($data as $table_name => $table_data) {
    if (isset($data[$table_name][$field_name])) {
      $field_label = $data[$table_name][$field_name]['title'];
      break;
    }
  }
  foreach ($data as $table_name => $table_data) {
    $data[$table_name][$field_name . '_proximity'] = [
      'group' => $table_data[$field_name . '_value']['group'],
      'title' => t('@label Proximity (@field_name)', [
        '@label' => $field_label,
        '@field_name' => $field_name,
      ]),
      'help' => $table_data[$field_name . '_value']['help'],
      'field' => [
        'id' => 'geofield_proximity_field',
        'real field' => $field_name,
        'float' => TRUE,
        'click sortable' => TRUE,
        'additional fields' => [
          'latitude' => [
            'field' => $field_name . '_lat',
          ],
          'longitude' => [
            'field' => $field_name . '_lon',
          ],
        ],
      ],
      'filter' => [
        'id' => 'geofield_proximity_filter',
        'real field' => $field_name,
      ],
      'sort' => [
        'id' => 'geofield_proximity_sort',
        'real field' => $field_name,
      ],
    ];
  }

  return $data;
}
